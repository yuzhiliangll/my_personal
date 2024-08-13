#include <iostream>
using namespace std;


#if 0
#include <mutex>

// 懒汉模式-> 什么时候使用时这个单例对象, 在使用的时候再去创建对用的实例
/*
    这样会导致线程不安全, 多个线程同时调用getInstance()方法, 会创建多个实例
    所以需要加互斥锁
    两个嵌套的 if 来判断单例对象是否为空的操作就叫做双重检查锁定。--20240812


    20240813--双重检查锁定的问题

    1. 在编译器优化时，可能会对指令进行重排序，导致在多线程下出现错误。
    2. 在某些情况下，双重检查锁定可能会导致死锁。

    假设有两个线程A, B, 当线程A 执行到第 59 行时在线程A中 TaskQueue 实例对象 被创建，并赋值给 m_taskQ。

    但是实际上 m_taskQ = new TaskQueue; 在执行过程中对应的机器指令可能会被重新排序。正常过程如下：

        第一步：分配内存用于保存 TaskQueue 对象。

        第二步：在分配的内存中构造一个 TaskQueue 对象（初始化内存）。

        第三步：使用 m_taskQ 指针指向分配的内存。

    但是被重新排序以后执行顺序可能会变成这样：

        第一步：分配内存用于保存 TaskQueue 对象。

        第二步：使用 m_taskQ 指针指向分配的内存。

        第三步：在分配的内存中构造一个 TaskQueue 对象（初始化内存）。
    
    这样重排序并不影响单线程的执行结果，但是在多线程中就会出问题。
    如果线程A按照第二种顺序执行机器指令，执行完前两步之后失去CPU时间片被挂起了，
    此时线程B在第55行处进行指针判断的时候m_taskQ 指针是不为空的，但这个指针指向的内存却没有被初始化，
    最后线程 B 使用了一个没有被初始化的队列对象就出问题了（出现这种情况是概率问题，需要反复的大量测试问题才可能会出现）。

    在C++11中引入了原子变量atomic ---> 在底层可以控制机器指令的执行顺序, 通过原子变量可以实现一种更安全的懒汉模式的单例，代码如下：
*/
#include <atomic>
class TaskQueue
{
public:
    // TaskQueue() = delete;
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;

    static TaskQueue* getInstance()// ---在静态函数里只能使用静态变量
    {
        TaskQueue* task = m_taskQ.load(); // 获取原子变量m_taskQ的值
        if (task == nullptr) 
        {
            m_mutex.lock();// 加锁-- 是其他线程阻塞
            task = m_taskQ.load();
            if (task == nullptr) // 双重检查
            {
                task = new TaskQueue;// 分配内存
                m_taskQ.store(task);// 将指针存入原子变量m_taskQ中
            }            
            m_mutex.unlock();// 一定要解锁
        }
        return task; // 返回指针
    }
    /*
        上面代码中使用原子变量atomic的store() 方法来存储单例对象，使用load() 方法来加载单例对象。
        在原子变量中这两个函数在处理指令的时候默认的原子顺序是memory_order_seq_cst（顺序原子操作 - sequentially consistent），
        使用顺序约束原子操作库，整个函数执行都将保证顺序执行，并且不会出现数据竞态（data races），
        不足之处就是使用这种方法实现的懒汉模式的单例执行效率更低一些。
    */

    void print()
    {
        cout << "我是单例对象的一个成员函数" << endl;
    }

private:
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;


    // static TaskQueue* m_taskQ;// 静态变量不允许在类内部进行初始化---它用来保存唯一的 TaskQueue 实例。
    static mutex m_mutex;// 静态互斥锁
    static atomic<TaskQueue*> m_taskQ;// 原子变量--对应任务队列----目的: 通过原子变量把类的实例对象保存导致指针里面

};
// TaskQueue* TaskQueue::m_taskQ = nullptr;// 外部初始化 可以指定为空  /  也可以创建了 TaskQueue 的唯一实例。
atomic<TaskQueue*> TaskQueue::m_taskQ;// 原子变量, 只需声明,不需要赋初始值
mutex TaskQueue::m_mutex;

#endif

/*
    m_mutex.lock();  // 加锁: 方式1
    m_mutex.unlock();


    std::mutex m_mutex; // 声明一个互斥锁
    std::lock_guard<std::mutex> locker(m_mutex); // 使用 lock_guard 对互斥锁进行自动加锁

    在 locker 对象的生命周期内，m_mutex 都会被锁定，当 locker 对象被销毁时，m_mutex 会自动解锁。

    工作原理：
    加锁：
    当 std::lock_guard<std::mutex> locker(m_mutex); 这一行代码被执行时，locker 对象被创建，同时对 m_mutex 进行加锁。
    自动解锁：
    当 locker 对象离开作用域时（例如函数结束或者异常抛出），locker 会自动析构，释放 m_mutex 的锁。
    方式2的解释：
    “方式2” 表示这是另一种对 std::mutex 进行加锁的常见方法，通常相对于手动调用 m_mutex.lock() 和 m_mutex.unlock() 的方式。

    优点：
    安全性：使用 std::lock_guard 可以确保无论在什么情况下（包括异常）都能正确解锁，避免因忘记解锁而导致的死锁问题。

    简洁性：简化了代码，不需要手动编写解锁逻辑。
*/

#if 1
#include <mutex>

// 懒汉模式-> 什么时候使用时这个单例对象, 在使用的时候再去创建对用的实例
/*
    使用静态局部对象解决线程安全问题 ---> 编译器必须支持C++11
    静态局部对象在程序运行期间只会被初始化一次，并且只会被初始化一次，因此可以保证全局只有一个实例存在。
    这种方法实现的单例模式比较简单，但是缺点是每次使用该单例对象时都需要先调用 getInstance() 方法，这可能会增加程序的复杂性。


*/
#include <atomic>
class TaskQueue
{
public:
    // TaskQueue() = delete;
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;

    static TaskQueue* getInstance()// ---在静态函数里只能使用静态变量
    {
        static TaskQueue task; // 静态局部变量--在全局数据区，程序运行期间只会被初始化一次
        return &task; // 返回指针
    }
    /*
        定义了一个静态局部队列对象，并且将这个对象作为了唯一的单例实例。
        使用这种方式之所以是线程安全的，是因为在C++11标准中有如下规定，并且这个操作是在编译时由编译器保证的：

        如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化。

        最后总结一下懒汉模式和饿汉模式的区别：

        懒汉模式的缺点是在创建实例对象的时候有安全问题，但这样可以减少内存的浪费（如果用不到就不去申请内存了）。
        饿汉模式则相反，在我们不需要这个实例对象的时候，它已经被创建出来，占用了一块内存。
        对于现在的计算机而言，内存容量都是足够大的，这个缺陷可以被无视。
    */
    void print()
    {
        cout << "我是单例对象的一个成员函数" << endl;
    }

private:
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;


};
#endif

int main()
{
    TaskQueue* taskQ = TaskQueue::getInstance();// 获取单例实例
    taskQ->print();

    return 0;
}



