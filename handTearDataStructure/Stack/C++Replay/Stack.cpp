#include "Stack.h"

template <typename T>
Stack<T>::Stack(int size) : capacity(size), topIndex(-1)// 初始化
{
    data = new T[capacity];// 动态分配内存
}

template <typename T>
Stack<T>::~Stack()// 析构函数
{
    delete[] data;// 释放内存
}

template <typename T>
void Stack<T>::push(const T& value)// 入栈
{
    if (isFull())// 判断栈是否已满
    {
        std::cerr << "Stack is full!" << std::endl;
        return;
    }
    data[++topIndex] = value;// 将元素放入栈顶
}

template <typename T>
void Stack<T>::pop()// 出栈
{
    if (isEmpty())// 判断栈是否为空
    {
        std::cerr << "Stack is empty!" << std::endl;
        return;
    }
    --topIndex;// 栈顶指针下移
}

template <typename T>
T Stack<T>::top() const// 返回栈顶元素
{
    if (isEmpty())// 判断栈是否为空
    {
        std::cerr << "Stack is empty!" << std::endl;
        throw std::out_of_range("Stack is empty!");// 抛出异常
    }
    return data[topIndex];// 返回栈顶元素
}

template <typename T>
bool Stack<T>::isEmpty() const// 判断栈是否为空
{
    return topIndex == -1;
}

template <typename T>
bool Stack<T>::isFull() const// 判断栈是否已满
{
    return topIndex == capacity - 1;// 栈顶指针等于容量减一，则栈已满
}

template <typename T>
int Stack<T>::size() const// 返回栈中元素个数
{
    return topIndex + 1;
}

// Explicit instantiation for common types
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;

