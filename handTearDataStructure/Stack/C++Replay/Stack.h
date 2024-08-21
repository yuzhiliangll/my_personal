#ifndef __STACK_CPP__
#define __STACK_CPP__


#include <iostream>

template <typename T>
class Stack
{
private:
    T* data;     // 动态数组存储栈元素
    int topIndex;// 栈顶索引
    int capacity; // 栈容量

public:
    Stack(int size = 10);  // 构造函数，默认大小为10
    ~Stack();              // 析构函数

    void push(const T& value); // 入栈
    void pop();                // 出栈
    T top() const;                  // 获取栈顶元素
    bool isEmpty() const;             // 判断栈是否为空
    bool isFull() const;              // 判断栈是否已满
    int size() const;                 // 获取栈中元素个数
};


#endif // __STACK_CPP__