#pragma once

#include <iostream>

template <typename T>
class Queue
{
private:
    T* data; // 动态数组存储队列元素
    int frontIndex; // 队头索引
    int rearIndex; // 队尾索引
    int capacity; // 队列容量
    int count; // 队列中元素的大小

public:
    Queue(int size = 10);  // 构造函数，默认大小为10
    ~Queue();              // 析构函数

    void enqueue(const T& value);  // 入队操作
    void dequeue();                // 出队操作
    T front() const;            // 获取队头元素
    bool isEmpty() const;       // 判断队列是否为空
    bool isFull() const;        // 判断队列是否已满
    int size() const;           // 获取队列中元素的个数

};



