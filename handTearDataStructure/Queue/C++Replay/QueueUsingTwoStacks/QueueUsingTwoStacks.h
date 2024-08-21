#pragma once

#include <stack>
#include <stdexcept>

template <typename T>
class QueueUsingTwoStacks
{
private:
    std::stack<T> stack1;
    std::stack<T> stack2;

    // 将 stack1 中的元素依次弹出并压入 stack2 中
    void transferElements()
    {
        while (!stack1.empty())// stack1 不为空
        {
            stack2.push(stack1.top());// stack2 压入 stack1 的栈顶元素
            stack1.pop();// stack1 弹出栈顶元素
        }
    }

public:
    QueueUsingTwoStacks() = default;

    // 入队操作
    void push(const T& value)
    {
        stack1.push(value);// stack1 压入 value
    }

    // 出队操作
    void pop()
    {
        if (stack2.empty()) // stack2 为空
        {
            if (stack1.empty()) // stack1 也为空
            {
                throw std::runtime_error("Queue is empty");
            }
            transferElements(); // 将 stack1 中的元素依次弹出并压入 stack2 中
        }
        if (!stack2.empty()) // 确保 stack2 仍有元素
        {
            stack2.pop(); // stack2 弹出栈顶元素
        }
        else
        {
            throw std::runtime_error("Queue is empty");
        }
    }

    // 获取队首元素
    T peek() const
    {
        if (stack2.empty()) // stack2 为空
        {
            if (stack1.empty()) // stack1 也为空
            {
                throw std::runtime_error("Queue is empty");
            }
            // 使用 const_cast 对 const 对象调用非 const 成员函数
            const_cast<QueueUsingTwoStacks*>(this)->transferElements(); // 将 stack1 中的元素依次弹出并压入 stack2 中
        }
        if (!stack2.empty()) // 确保 stack2 仍有元素
        {
            return stack2.top(); // 返回 stack2 的栈顶元素
        }
        else
        {
            throw std::runtime_error("Queue is empty");
        }
    }

    // 判断队列是否为空
    bool isEmpty() const 
    {
        return stack1.empty() && stack2.empty();
    }

};


