#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>// 多线程
using namespace std;


#if 1
// 利用饿汉模式写一个 任务队列
/*
    作为程序猿的我们，如果想给巴基的账本升级成一个应用程序，首要任务就是设计一个单例模式的任务队列，那么就需要赋予这个类一些属性和方法：

    属性：
        存储任务的容器，这个容器可以选择使用STL中的队列（queue)
        互斥锁，多线程访问的时候用于保护任务队列中的数据

    方法：主要是对任务队列中的任务进行操作
        任务队列中任务是否为空
        往任务队列中添加一个任务
        从任务队列中取出一个任务
        从任务队列中删除一个任务
    根据分析，就可以把这个饿汉模式的任务队列的单例类定义出来了：
*/

/*
    饿汉模式没有线程安全问题, 说的是当多个线程在访问 这个单例对象的时候没有线程安全问题

    但是当访问单例对象的内部数据时候会有线程安全问题--- 多个线程共享资源的问题, 所以需要加锁

    为了保证数据安全性--只能牺牲效率
*/
class TaskQueue
{
public:
    // TaskQueue() = delete;
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;

    static TaskQueue* getInstance()
    {
        return m_taskQ; // 返回静态属性
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数" << endl;
    }

    // 判断任务队列是否为空
    bool isEmpty()
    {
        lock_guard<mutex> locker(m_mutex);
        bool flag = m_data.empty();
        return flag; // return m_data.empty();
    }

    // 添加任务
    void addTask(int task)
    {
        lock_guard<mutex> locker(m_mutex);
        m_data.push(task);
    }

    // 删除任务
    bool popTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if (m_data.empty())
        {
            return false;
        }
        m_data.pop();//只能删除对头元素
        return true;
    }

    // 获取任务--不删除
    int takeTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(m_data.empty())
        {
            return -1;
        }
        int task = m_data.front();
        return task;
    }

private:
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;

    static TaskQueue* m_taskQ;// 静态变量不允许在类内部进行初始化---它用来保存唯一的 TaskQueue 实例。

    // 定义任务队列
    queue<int> m_data;
    mutex m_mutex; // 互斥锁-- 保护共享资源
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;// 外部初始化 可以指定为空  /  也可以创建了 TaskQueue 的唯一实例。
#endif


int main()
{
    TaskQueue* taskQ = TaskQueue::getInstance();// 获取单例实例--确保整个程序中只有一个任务队列实例存在。
    
    // 生产者
    /*
        thread t1([=](){ ... }); 是使用 Lambda 表达式来创建和启动一个线程的方式。
        这里的 [=] 是 Lambda 表达式的捕获列表，{ ... } 是 Lambda 表达式的函数体。

        Lambda 表达式允许你定义一个匿名函数，它可以在需要函数对象的地方使用。在这个例子中，Lambda 表达式定义了一个函数，该函数没有参数，并且没有返回值。

        Lambda 表达式是一种匿名函数，常用于创建短小的内联函数。它的基本语法是
        [capture]：捕获列表，定义了 Lambda 表达式如何访问外部变量。
        (parameters)：参数列表（可选），定义了 Lambda 的参数。
        -> return_type：返回类型（可选，如果可以推断则省略）。
        {}：函数体，包含要执行的代码。

        2. 捕获列表 [=]：
        [=] 表示按值捕获外部作用域中的所有变量。Lambda 表达式内部可以使用这些外部变量的拷贝，而不会修改原变量。

        捕获列表可以有不同的形式：

        [&]：按引用捕获所有变量，Lambda 表达式可以修改外部变量。
        [this]：捕获当前类的 this 指针，用于访问类的成员变量和函数。
        [a, &b]：按值捕获变量 a，按引用捕获变量 b。
    */
    thread t1([=](){
        for (size_t i = 0; i < 10; i++)
        {
            /* code */
            taskQ->addTask(i + 100);// 向任务队列添加任务
            cout<< "+++ push data : " << i + 100 << ", threadID: " << 
                this_thread::get_id() << endl;//日志输出：每次添加任务后，打印日志，输出当前数据和线程ID。
            this_thread::sleep_for(chrono::milliseconds(500));// 休眠一段时间
        }

    });
    

    // 消费者
    thread t2([=](){
        this_thread::sleep_for(chrono::milliseconds(100));// 休眠一段时间
        while(!taskQ->isEmpty())// 消费的时候--判断队列是否为空
        {
            /* code */
            int num = taskQ->takeTask();
            cout<< "+++ take data : " << num << ", threadID: " << 
                this_thread::get_id() << endl;
            taskQ->popTask();// 从任务队列中移除任务
            this_thread::sleep_for(chrono::milliseconds(1000));// 休眠一段时间-- 让生产者生产的快一点,让消费者消费的快一点
        }

    });
    // 确保主线程等待生产者和消费者线程执行完毕后才继续执行，避免程序提前结束。
    t1.join(); // 阻塞主线程，等待生产者线程结束
    t2.join(); // 阻塞主线程，等待消费者线程结束
    
    return 0;
}

/*
    join() 是 C++ 标准库中的一个方法，属于 std::thread 类，用于等待线程完成执行。
    具体来说，它会阻塞调用它的线程（通常是主线程），直到被调用的线程完成执行为止。

    join() 的用途
    线程同步：确保当前线程（通常是主线程）在执行后续代码之前等待其他线程完成。
    例如，在创建多个线程来执行并发任务时，使用 join() 可以确保所有线程在主线程继续执行之前都已经完成任务。

    防止资源泄漏：如果一个线程在其生命周期结束前没有被 join() 或 detach()，则该线程对象的析构函数会抛出一个异常。
    join() 可以避免这种情况。

    #include <iostream>
    #include <thread>

    void task1() {
        std::cout << "Task 1 is running" << std::endl;
    }

    void task2() {
        std::cout << "Task 2 is running" << std::endl;
    }

    int main() {
        std::thread t1(task1); // 创建并启动线程 t1
        std::thread t2(task2); // 创建并启动线程 t2

        t1.join(); // 等待 t1 完成执行
        t2.join(); // 等待 t2 完成执行

        std::cout << "All tasks completed" << std::endl;
        return 0;
    }

    代码解释
创建线程：

std::thread t1(task1); 创建并启动线程 t1，执行 task1 函数。
std::thread t2(task2); 创建并启动线程 t2，执行 task2 函数。
等待线程结束：

t1.join(); 阻塞主线程，直到 t1 线程执行完毕。
t2.join(); 阻塞主线程，直到 t2 线程执行完毕。
继续执行：

当 t1 和 t2 都执行完毕后，主线程才会继续执行，输出 "All tasks completed"。
注意事项
必须调用：如果你创建了一个线程，但没有调用 join() 或 detach()，程序可能会抛出异常或者出现未定义行为。
不可重复调用：join() 只能对一个线程调用一次。如果在同一个线程上多次调用 join()，会抛出异常。
不能与 detach() 混用：如果一个线程已经调用了 detach()，就不能再调用 join()。detach() 会将线程与其线程对象分离，使线程在后台独立运行。
*/
