#include <iostream>
using namespace std;


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
    // 把访问权限设置为私有的，防止外部直接访问
    // 或者 删除 任选其一
    TaskQueue() = default;// 构造函数被设为 private，确保无法从类外部创建 TaskQueue 的实例
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;



    // 我们把创建对象的活路全部堵死了
    // 只能通过类名访问静态属性或方法 --- 只有静态的才会属于类本身
    // 定义一个静态的指针变量，指向唯一的实例
    static TaskQueue* m_taskQ;// 静态变量不允许在类内部进行初始化---它用来保存唯一的 TaskQueue 实例。
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;// 外部初始化 可以指定为空  /  也可以创建了 TaskQueue 的唯一实例。

int main()
{
    TaskQueue* taskQ = TaskQueue::getInstance();// 获取单例实例
    taskQ->print();

    return 0;
}

/*
    关键点：
单例模式的核心：确保一个类只有一个实例，并提供对该实例的全局访问点。
这里通过私有的构造函数、删除拷贝构造和赋值运算符，确保类无法被外部创建或复制，唯一的实例通过静态成员变量 m_taskQ 管理。

线程安全性：
此实现的单例模式并不是线程安全的。
如果在多线程环境中第一次调用 getInstance()，可能会创建多个实例。为了实现线程安全，可以使用双重检查锁定（Double-Checked Locking）或 std::call_once 等机制。

优点：
确保全局范围内只能有一个 TaskQueue 实例。
提供一个全局访问点，使用简单。
缺点：
没有考虑线程安全。
静态初始化可能在程序退出时产生未定义行为，需要特殊处理（如将 m_taskQ 改为智能指针）
*/


