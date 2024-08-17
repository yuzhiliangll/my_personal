/*
    编写一个异步线程池:
    基本思想: 预先创建一定数量的线程, 并将他们放入一个池中, 线程池负责管理线程的生命周期
    并将任务分配给空闲任务线程执行, 当任务执行完毕后, 线程会继续等待新的任务, 而不是立即销毁
    这样避免了在执行任务时频繁的创建和销毁线程的开销, 提高了程序的性能和稳定性

    它的组成如下:

    线程池管理类: 负责创建、销毁线程, 维护线程池状态(如空闲线程、忙碌线程等)

    任务队列:     用于存储待执行的任务。任务通常以函数对象（如 std::function）的形式存储。

    工作线程:     线程池中的实际线程，它们从任务队列中取出任务并执行。

    同步机制:     用于保护任务队列和线程池状态的线程安全操作，通常使用互斥锁和条件变量。

*/

/*
    在设计线程池时，我们需要考虑以下几个重要原则：

    线程池大小管理：
    固定大小：线程池中的线程数量固定不变。适用于负载比较稳定的场景。
    动态调整：根据任务负载动态调整线程池大小。适用于负载变化较大的场景。

    任务队列管理：
    FIFO 队列：最常用的任务队列实现方式，按照任务提交的顺序执行任务。
    优先级队列：根据任务的优先级执行任务，适用于需要按优先级处理任务的场景。

    线程安全：
    互斥锁：用于保护共享资源（如任务队列）的访问。
    条件变量：用于线程之间的通信，如通知空闲线程有新的任务到来。
    原子变量：对原子变量的操作都是原子操作，它是线程安全的。---------它能保证自身对象里的数据在变化的过程中是不会失去CPU时间片的

原子变量 是一种特殊的变量，保证对其执行的操作是 原子性 的，
这意味着这些操作要么完全执行，要么完全不执行，不会被其他线程打断。
因此，原子变量的操作是线程安全的。
-------------使用了原子变量 -->就会减少了 互斥锁的使用


    任务执行与错误处理：
    任务执行过程中的异常需要适当处理，以避免线程池中的线程因未捕获异常而终止。

注：
    1. 
    在多线程编程中，"休眠"通常指的是线程从运行态（正在执行的状态）变为就绪态（等待执行的状态）。
    当一个线程失去CPU资源（即被调度器暂停执行），
    它需要保存当前的执行上下文（如寄存器数据）以便之后恢复执行时能够继续。
    这个过程称为"上下文切换"。
    当线程被唤醒（即重新获得CPU资源）时，它需要恢复之前保存的执行上下文，然后继续执行。
    这个过程称为"上下文恢复"。

    然而，在某些情况下，如果线程被暂停时寄存器中的数据没有及时被写入到内存，那么当其他线程访问这些数据时，可能会读取到旧的数据（即未被更新的值）。
    这可能会导致数据不一致的问题，特别是在多线程共享数据的情况下。
    因此，为了避免这种情况，我们通常需要使用互斥锁（mutex）来保护共享数据的访问，以确保在多线程环境下数据的一致性。

    2. 
    使用互斥锁的目的就是为了在新数据没有从寄存器同步到内存之前, 不让其他线程访问这块内存资源
    从而保证数据的一致性
*/

/*
    具体理解：

    寄存器与内存的区别：

    寄存器是CPU内部的高速存储单元，用于存储当前正在处理的数据。
    内存（如RAM）是外部的存储单元，速度较慢，用于存储程序和数据。
    
    线程休眠与上下文切换：
    当一个线程休眠（失去CPU资源）时，操作系统会进行上下文切换，将当前线程的执行状态（包括寄存器的值）保存起来，并调度其他线程运行。
    如果上下文切换过程中，寄存器中的数据没有及时刷新回内存，那么内存中的数据依旧是线程运行前的旧数据。
    
    数据不一致问题：
    其他线程在访问共享变量时，可能会访问到内存中旧的、未被更新的数据，导致数据不一致，影响程序的正确性。
    
    解决方案：
    内存屏障（Memory Barrier）：确保在上下文切换前，寄存器的数据会被及时写入到内存中。
    锁机制：通过互斥锁等同步机制来确保线程对共享数据的访问是安全的，避免数据竞争。
    volatile 关键字：在某些情况下，可以使用 volatile 关键字告诉编译器不要对变量进行优化，从而确保每次访问变量时都是从内存中读取。
*/
/*********************************************************************************************************************** */

/**
 * 构成:
 *      1.管理者线程 -> 本质是还是一个子线程, 1个
 *              --作用: 控制工作线程的数量 -- 增加或减少
 * 
 *      2.工作线程  -> 本质是还是一个子线程, n个
 *              --作用: 从任务队列中取任务, 并处理
 *              --若任务队列为空, 被阻塞(被条件变量阻塞)
 *              --最后又因为 任务队列是共享资源, 所以需要线程同步(互斥锁保护)
 *              
 *              -- 在程序执行期间, 我们还需要知道当前工作线程的数量
 *              -- 所以需要使用一个变量来记录当前工作线程的数量 以及空闲的线程数量
 *              -- 还需要有最小, 最大线程数量
 * 
 *      3.任务队列  -> stl->queue
 *            --作用: 存放任务
 *            --互斥锁
 *            --条件变量
 * 
 *     4. 线程池开关 -> bool
 */

#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <map>
#include <future>
using namespace std;

/*
    template<typename F, typename... Args>
    auto addTask(F&& f, Args&&... args) -> future<typename result_of<F(Args...)>::type>

    这个函数模板是 ThreadPool 类中用于添加任务到线程池的一个模板函数。
    它允许你将任意的可调用对象（如函数、lambda 表达式、函数对象等）和其参数传递给线程池，
    并获取一个 std::future 对象来异步获取任务的执行结果。
    ===========================================================================================

    1. 模板参数与返回类型
    template<typename F, typename... Args>:

    F 是任务的类型，可以是函数、lambda 表达式、或者其他可调用对象。
    Args... 是传递给任务的参数类型的可变参数包。
    auto 和 -> future<typename result_of<F(Args...)>::type>:

    使用 auto 和后置返回类型（trailing return type）指定返回值类型为 std::future。
    result_of<F(Args...)>::type 获取任务 f 调用时的返回类型，例如，如果 f 是一个返回 int 的函数，那么 result_of<F(Args...)>::type 将是 int，
    所以最终返回的类型是 std::future<int>。

    2. 创建任务
    using returnType = typename result_of<F(Args...)>::type;
    auto task = make_shared<packaged_task<returnType()>>(
        bind(forward<F>(f), forward<Args>(args)...)
    
    using returnType = typename result_of<F(Args...)>::type;:
    定义 returnType 为任务执行后返回的类型。
    
    make_shared<packaged_task<returnType()>>:
    packaged_task<returnType()> 是一个封装了可调用对象的类，可以在将来某个时候调用并获取其返回值。
    使用 bind(forward<F>(f), forward<Args>(args)...) 将任务 f 和参数 args 绑定成一个无参函数。forward 确保了正确的传递参数类型（值类型、左值引用、右值引用）。
    
    auto task:
    task 是一个 shared_ptr，指向封装了任务的 packaged_task 对象。

    3. 获取任务的 future 对象
    task->get_future():
    获取与 packaged_task 关联的 std::future 对象，用来在任务完成后获取结果。
    
    4. 将任务添加到任务队列
    {
    unique_lock<mutex> lock(m_queueMutex);
    m_tasks.emplace([task]() { (*task)(); });
    }
    m_condition.notify_one();

    unique_lock<mutex> lock(m_queueMutex);:

    使用 unique_lock 对任务队列的互斥量 m_queueMutex 加锁，以保护对共享资源 m_tasks 的访问。
    
    m_tasks.emplace([task]() { (*task)(); });:
    将一个 lambda 函数添加到任务队列 m_tasks 中，这个 lambda 函数会在某个线程池线程中被执行。具体来说，这个 lambda 负责调用 task，执行封装的任务。
    
    m_condition.notify_one();:
    通知一个等待在条件变量 m_condition 上的线程，让它知道有新任务加入，并可以继续执行。
    
    5. 返回 future 对象
    最后，返回之前获取的 future 对象 res，供调用者用来获取任务执行结果。

);

*/

class ThreadPool
{
public:
    ThreadPool(int min = 4, int max = thread::hardware_concurrency());
    ~ThreadPool();
    void addTask(function<void()> f);
    template<typename F, typename... Args>
    auto addTask(F&& f, Args&&... args) -> future<typename result_of<F(Args...)>::type>
    {
        // 1. packaged_task 包装任务函数
        using returnType = typename result_of<F(Args...)>::type;// 使用 result_of<F(Args...)>::type 来获取任务函数 F 执行后的返回类型，并将其命名为 returnType
        auto task = make_shared<packaged_task<returnType()>>(
            bind(forward<F>(f), forward<Args>(args)...)// 完美转发，将任务函数 f 和参数 args 传递给 packaged_task
        );
        // 2. future 获取任务结果
        future<returnType> res = task->get_future();// get_future 返回一个 future 对象，这个对象用于获取异步任务的结果。
        
        // 3. 将任务函数加入任务队列
        {
            unique_lock<mutex> lock(m_queueMutex);//  用于加锁，确保线程安全地将任务加入任务队列。
            m_tasks.emplace([task]() { (*task)(); });// 将任务添加到任务队列中。这里使用了一个 lambda 函数来调用 (*task)()，即执行封装的任务。
        }
        m_condition.notify_one();// 用于通知等待的线程（如果有的话）任务队列中有新的任务可用。
        return res;
    }
    /*
        总结
            这个函数模板允许你将任意的任务（函数、lambda 等）和参数提交给线程池，
            它会将任务包装成 packaged_task 对象，放入任务队列中，并返回一个 std::future，你可以使用这个 future 在稍后获取任务的执行结果。
            这个设计使得任务的提交和执行完全异步化，并且任务的结果可以被安全地获取。
    */

private:
    void manager();
    void worker();
private:
    thread* m_manager;
    map<thread::id, thread> m_workers;
    vector<thread::id> m_ids;
    int m_minThreads;
    int m_maxThreads;
    atomic<bool> m_stop;
    atomic<int> m_curThreads;
    atomic<int> m_idleThreads;
    atomic<int> m_exitNumber;
    queue<function<void()>> m_tasks;
    mutex m_idsMutex;
    mutex m_queueMutex;
    condition_variable m_condition;
};


