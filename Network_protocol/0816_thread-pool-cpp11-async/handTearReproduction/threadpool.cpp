#if 0
#include "threadpool.h"
#include <iostream>


// 初始化的方式有两种
/*
    第一种: 写在初始化列表里--叫初始化-- 这种效率更高
    第二种: 写在构造函数里 -- 这叫赋值
*/
ThreadPool::ThreadPool(int min, int max) : m_maxThread(max), 
                                           m_minThread(min), 
                                           m_stop(false),
                                           m_idleThread(min),
                                           m_curThread(min)
{
    // 创建管理者线程
    m_manager = new thread(&ThreadPool::manager, this);// 如果是类里面的成员函数，需要加this

    // 创建工作线程
    for (int i = 0; i < min; ++i)
    {
        // 创建线程对象
        thread t(&ThreadPool::worker, this);
        // 将线程对象保存到容器中
        /*
            注意:
                这里使用emplace_back()函数，而不是push_back()函数
                因为emplace_back()函数可以直接将参数传递给构造函数，而push_back()函数需要先创建一个对象，然后再将对象插入到容器中
                这里使用emplace_back()函数，可以避免创建临时对象，提高效率
                --------------------------------------------------------------------
                emplace_back() 需要在添加的过程中去构造对象才能避免拷贝和移动
                也就是需要在函数的括号中去构造要添加的对象
        */
        m_workers.insert(make_pair(t.get_id(), move(t))); // 里面是一个匿名对象直接放到 容器里面, 匿名对象会自动调用构造函数,
        // 里面的匿名对象什么时候 销毁, 当把他从容器中弹出的时候 销毁,, 不弹出就不会销毁

    }

}

ThreadPool::~ThreadPool()
{
    m_stop = true;
    m_condition.notify_all();// 唤醒所有线程
    for (auto& it : m_workers)// 线程对象是不允许拷贝的, 所以用引用
    {
        thread& t = it.second;
        if (t.joinable())
        {
            cout << "******** 线程 " << t.get_id() << " 将要退出了..." << endl;

            t.join();// 阻塞当前的线程, 等待子线程执行完毕, 执行完毕后 退出任务函数

        }
    }
    if (m_manager->joinable())
    {
        m_manager->join();
    }
    delete m_manager;
}


// 添加任务 -》 任务队列
/*
    线程池里面的任务队列是 共享资源的
    取任务时必须要线程同步, 使用互斥锁
    1. 一般的 加锁解锁
    2. 高级一点的--使用自动管理的  目的就是->避免死锁        就像之前的智能指针一样
        lock_guard<mutex> lock(m_mutex);
*/
void ThreadPool::addTask(function<void(void)> task)
{
    // {} 限定了某些变量 作用域的范围
    {
        lock_guard<mutex> locker(m_queueMutex);
        m_tasks.emplace(task);
    }// locker 出了这个作用域就会被析构, 里面的锁也会被释放
    
    // 唤醒
    m_condition.notify_one();// 这里为什么不需要锁 以及 使 locker 提前析构--加作用域

}

void ThreadPool::manager(void)// 对于管理者线程而言, 如果线程池不关闭, 他也要一直 执行manage函数里面的动作并且 重复进行相同的内容
{
    while(!m_stop.load())// 只要线程池不退出
    {
        // 检测工作线程的数量-- 按固定的频率
        this_thread::sleep_for(chrono::seconds(3));

        int idel = m_idleThread.load();// 空闲的线程
        int cur = m_curThread.load();
        if(idel > cur / 2 && cur > m_minThread)
        {
            // 每次销毁两个线程
            m_exitThread.store(2);
            m_condition.notify_all();// 唤醒所有阻塞在该条件变量上的线程
            unique_lock<mutex> lck(m_idsMutex);
            for(const auto& id : m_ids)// 对 m_ids 里面的线程遍历进行销毁
            {
                auto it = m_workers.find(id);// 搜索
                if(it != m_workers.end())
                {
                    std::cout << "############# thread " << (*it).first << "is destroyed!" << std::endl;
                    (*it).second.join();// 等待线程结束
                    m_workers.erase(it);// 删除 -- 从map容器里移除 就自动销毁
                }
            }
            m_ids.clear();// 清空
        }
        else if(idel == 0 && cur < m_maxThread)// 添加线程
        {
            thread t(&ThreadPool::worker, this);
            std::cout << "++++++ add a thread, id: " << t.get_id() << std::endl;
            m_workers.insert(make_pair(t.get_id(), move(t)));
            m_curThread++;
            m_idleThread++;
        }
    }
}

// 处理任务队列里的任务 -- 相当于消费者
// 对于消费者线程而言: 当他进入到 任务函数里之后, 我们需要他一直在里面循环的
/*
    消费者线程在进入任务函数后需要一直循环，主要是为了持续处理任务队列中的任务。
    这种设计背后的原因可以归纳为以下几点：

    1. 任务队列可能为空：当任务队列中没有任务时，消费者线程需要等待新的任务到来。如果消费者线程退出，那么整个线程池将无法处理新的任务。
    2. 任务队列可能持续增加新任务：即使任务队列一开始为空，新的任务可能会被添加到队列中。消费者线程需要能够处理这些新任务，因此需要一直循环等待新任务。
    3. 线程池可能需要关闭：当线程池关闭时，消费者线程需要能够处理完当前的任务队列中的所有任务，然后退出。因此，消费者线程需要一直循环直到任务队列为空，并且线程池关闭标志被设置。
    4. 线程池可能需要动态调整线程数量：当线程池需要增加或减少线程数量时，消费者线程需要能够处理当前的任务队列中的所有任务，然后退出。因此，消费者线程需要一直循环直到任务队列为空，并且线程池关闭标志被设置。
    因此，消费者线程在进入任务函数后需要一直循环，主要是为了持续处理任务队列中的任务。

一个典型的消费者线程可能会在循环中执行以下步骤：

    检查任务队列是否为空。
    如果队列不为空，从队列中取出一个任务。
    执行任务。
    回到循环的开头，继续检查队列。
*/
void ThreadPool::worker(void) // 工作的线程的任务函数
{
    while(!m_stop.load())// 循环重复的进行从任务队列取数据 -> 处理数据的动作
    {
        function<void(void)> task = nullptr;// 定义一个任务指针
        
        {
            unique_lock<mutex> locker(m_queueMutex);// 互斥锁 -- 这里 unique_lock 的作用和 lock_guard 作用一样
            while (m_tasks.empty() && !m_stop)
            {
                m_condition.wait(locker);// 如果线程池没关闭并且任务队列为空，工作的线程被条件变量阻塞

                if (m_exitThread.load() > 0)
                {
                    m_exitThread--;
                    m_idleThread--;
                    m_curThread--;
                    std::cout << "thread exit, ID: " << std::this_thread::get_id() <<std::endl;
                    /* 到此线程退出完成了一半 */

                    unique_lock<mutex> lck(m_idsMutex);
                    m_ids.emplace_back(this_thread::get_id());// 将退出的线程id放入容器中
                    return;
                }

            }
            // 通过addTask往任务队列中添加了新任务之后，可以唤醒被条件变量阻塞的线程

            if (!m_tasks.empty())
            {
                std::cout << "取出一个任务..." << std::endl;
                // 拷贝会浪费存储空间, 所以这里使用move 方法, 将所有权进行转移
                task = move(m_tasks.front());// 从任务队列中取出一个任务
                m_tasks.pop();// 从任务队列中删除这个任务
            }
        }// 这样使得 locker 在此作用域内生效, 并且 locker 在此作用域失效时, 会自动调用 unlock() 函数

        if(task)
        {
            m_idleThread--; // 原子变量 线程是安全的
            task(); // 执行任务
            m_idleThread++; // 
        }

    }
}

/*
    总结:
    void worker(): 工作的线程的任务函数

        工作的线程在该函数内部通过while (!m_stop.load())循环重复的进行从任务队列取数据 -> 处理数据的动作
        如果线程池没关闭并且任务队列为空，工作的线程被条件变量阻塞
        通过addTask往任务队列中添加了新任务之后，可以唤醒被条件变量阻塞的线程

    void manager()：管理者线程的任务函数

        通过睡眠的方式每隔一段时间对线程池中的工作进行进行一次检测
        如果空闲线程数量 > 总线程数量的一半并且线程总数量大于最小线程数量，销毁两个工作的线程
        空闲线程为0并且线程总数量小于最大线程数，添加一个工作线程

    void addTask(function<void()> f)：

        添加新的任务到任务队列
        通过notify_one()唤醒一个被阻塞的工作线程
*/

void calc(int x, int y)
{
    int res = x + y;
    cout << "res = " << res << endl;
    this_thread::sleep_for(chrono::seconds(1));// 休眠时间
}

int main()
{
    ThreadPool pool(4);// 创建实例
    for (int i = 0; i < 10; ++i)
    {
        auto func = bind(calc, i, i * 2);// 函数绑定器
        pool.addTask(func);
    }
    getchar();// 防止程序退出, 阻塞主线程, 等待线程池中的线程执行完任务
    return 0;
}
#endif


#include "threadpool.h"
#include <iostream>

ThreadPool::ThreadPool(int min, int max) : m_maxThreads(max),
m_minThreads(min), m_stop(false), m_exitNumber(0)
{
    //m_idleThreads = m_curThreads = max / 2;
    m_idleThreads = m_curThreads = min;
    cout << "线程数量: " << m_curThreads << endl;
    m_manager = new thread(&ThreadPool::manager, this);
    for (int i = 0; i < m_curThreads; ++i)
    {
        thread t(&ThreadPool::worker, this);
        m_workers.insert(make_pair(t.get_id(), move(t)));
    }
}

ThreadPool::~ThreadPool()
{
    m_stop = true;
    m_condition.notify_all();
    for (auto& it : m_workers)
    {
        thread& t = it.second;
        if (t.joinable())
        {
            cout << "******** 线程 " << t.get_id() << " 将要退出了..." << endl;
            t.join();
        }
    }
    if (m_manager->joinable())
    {
        m_manager->join();
    }
    delete m_manager;
}

void ThreadPool::addTask(function<void()> f)
{
    {
        lock_guard<mutex> locker(m_queueMutex);
        m_tasks.emplace(f);
    }
    m_condition.notify_one();
}

void ThreadPool::manager()
{
    while (!m_stop.load())
    {
        this_thread::sleep_for(chrono::seconds(2));
        int idle = m_idleThreads.load();
        int current = m_curThreads.load();
        if (idle > current / 2 && current > m_minThreads)
        {
            m_exitNumber.store(2);
            m_condition.notify_all();
            unique_lock<mutex> lck(m_idsMutex);
            for (const auto& id : m_ids)
            {
                auto it = m_workers.find(id);
                if (it != m_workers.end())
                {
                    cout << "############## 线程 " << (*it).first << "被销毁了...." << endl;
                    (*it).second.join();
                    m_workers.erase(it);
                }
            }
            m_ids.clear();
        }
        else if (idle == 0 && current < m_maxThreads)
        {
            thread t(&ThreadPool::worker, this);
            cout << "+++++++++++++++ 添加了一个线程, id: " << t.get_id() << endl;
            m_workers.insert(make_pair(t.get_id(), move(t)));
            m_curThreads++;
            m_idleThreads++;
        }
    }
}

void ThreadPool::worker()
{
    while (!m_stop.load())
    {
        function<void()> task = nullptr;
        {
            unique_lock<mutex> locker(m_queueMutex);
            while (!m_stop && m_tasks.empty())
            {
                m_condition.wait(locker);
                if (m_exitNumber.load() > 0)
                {
                    cout << "----------------- 线程任务结束, ID: " << this_thread::get_id() << endl;
                    m_exitNumber--;
                    m_curThreads--;
                    m_idleThreads--;
                    unique_lock<mutex> lck(m_idsMutex);
                    m_ids.emplace_back(this_thread::get_id());
                    return;
                }
            }

            if (!m_tasks.empty())
            {
                cout << "取出一个任务..." << endl;
                task = move(m_tasks.front());
                m_tasks.pop();
            }
        }

        if (task)
        {
            m_idleThreads--;
            task();
            m_idleThreads++;
        }
    }
}

#if 0
void calc(int x, int y)
{
    int res = x + y;
    cout << "res = " << res << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

int main()
{
    ThreadPool pool(4);
    for (int i = 0; i < 10; ++i)
    {
        auto func = bind(calc, i, i * 2);
        pool.addTask(func);
    }
    getchar();
    return 0;
}
#else
int calc(int x, int y)
{
    int res = x + y;
    //cout << "res = " << res << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return res;
}

int main()
{
    ThreadPool pool(4);
    vector<future<int>> results;

    for (int i = 0; i < 10; ++i)
    {
        results.emplace_back(pool.addTask(calc, i, i * 2));
    }

    // 等待并打印结果
    for (auto&& res : results)
    {
        cout << "线程函数返回值: " << res.get() << endl;
    }

    return 0;
}
#endif
