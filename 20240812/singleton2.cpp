#include <iostream>
using namespace std;

#if 0
// 饿汉模式-> 定义类的时候创建单例对象===== 多线程场景下---没有线程安全问题

// 定义一个单例模式的任务队列
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

private:
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;


    static TaskQueue* m_taskQ;// 静态变量不允许在类内部进行初始化---它用来保存唯一的 TaskQueue 实例。
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;// 外部初始化 可以指定为空  /  也可以创建了 TaskQueue 的唯一实例。
#endif


#if 1
#include <mutex>

// 懒汉模式-> 什么时候使用时这个单例对象, 在使用的时候再去创建对用的实例
class TaskQueue
{
public:
    // TaskQueue() = delete;
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;

    static TaskQueue* getInstance()
    {
        // 双重检查-- 提高效率, 线程并不会执行里面的加锁解锁
        if (m_taskQ == nullptr) 
        {
            m_mutex.lock();// 加锁-- 是其他线程阻塞
            if (m_taskQ == nullptr) // 双重检查
                m_taskQ = new TaskQueue;// 懒汉模式 === 多线程场景下，会有线程安全问题------> 加互斥锁
            m_mutex.unlock();// 一定要解锁
        }
        return m_taskQ; // 返回静态属性
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数" << endl;
    }

private:
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;


    static TaskQueue* m_taskQ;// 静态变量不允许在类内部进行初始化---它用来保存唯一的 TaskQueue 实例。
    static mutex m_mutex;// 静态互斥锁

};
TaskQueue* TaskQueue::m_taskQ = nullptr;// 外部初始化 可以指定为空  /  也可以创建了 TaskQueue 的唯一实例。
mutex TaskQueue::m_mutex;

#endif


int main()
{
    TaskQueue* taskQ = TaskQueue::getInstance();// 获取单例实例
    taskQ->print();

    return 0;
}


