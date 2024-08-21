#ifndef __STACKUSINGTWOQUEUES_H__
#define __STACKUSINGTWOQUEUES_H__
/*
    使用两个队列实现栈的功能是一种经典的面试问题。可以通过以下两种主要方法来实现这个功能：

    在 push 操作时将新元素添加到一个队列，
    并在 pop 操作时通过另一个队列来模拟栈的行为。

    在 pop 操作时将所有元素从一个队列移动到另一个队列，
    模拟栈的行为，同时将新的元素添加到队列中。
*/
// 方法 1：在 push 操作时使用一个队列，pop 操作时使用另一个队列

#include <queue>
#include <stdexcept>

template <typename T>
class StackUsingTwoQueues 
{
private:
    std::queue<T> queue1;
    std::queue<T> queue2;

    // 将元素从 queue1 移动到 queue2中
    void transferElements()
    {
        while (queue1.size() > 1)// queue1中保留一个元素
        {
            queue2.push(queue1.front());// queue1的元素移动到queue2
            queue1.pop();// queue1的元素出队
        }
    }

public:
    StackUsingTwoQueues() = default;

    // 入栈操作
    void push(const T& value)
    {
        queue1.push(value);// 将元素添加到 queue1
    }

    // 出栈操作
    void pop()
    {
        if (queue1.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        transferElements();// 将 queue1 中的元素移动到 queue2
        queue1.pop();// 移除 queue1 中的最后一个元素（即栈顶元素）
        std::swap(queue1, queue2);// 交换 queue1 和 queue2
    }

    // 获取栈顶元素
    T top() const
    {
        if (queue1.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        std::queue<T> tempQueue = queue1;// 创建一个临时队列
        while (tempQueue.size() > 1)
        {
            tempQueue.pop();// 弹出元素
        }
        return tempQueue.front();// 返回最后一个元素
    }

    // 判断栈是否为空
    bool isEmpty() const
    {
        return  queue1.empty();
    }

};



#endif // __STACKUSINGTWOQUEUES_H__