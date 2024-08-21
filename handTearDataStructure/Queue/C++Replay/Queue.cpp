#include "Queue.h"


template <typename T>
Queue<T>::Queue(int size) : capacity(size), frontIndex(0), rearIndex(-1), count(0)
{
    data = new T[capacity];
}


template <typename T>
Queue<T>::~Queue()
{
    delete[] data;// 释放动态分配的内存
}

template <typename T>
void Queue<T>::enqueue(const T& value)// 入队
{
    if (isFull())
    {
        std::cerr << "Queue is full. Cannot enqueue new element." << std::endl;
        return;
    }

    rearIndex = (rearIndex + 1) % capacity;// 更新rearIndex，循环队列
    data[rearIndex] = value;// 将元素添加到队列的末尾
    count++;// 更新队列中的元素数量
}

template <typename T>
void Queue<T>::dequeue()// 出队
{
    if (isEmpty())
    {
        std::cerr << "Queue is empty. Cannot dequeue element." << std::endl;
        return;
    }

    frontIndex = (frontIndex + 1) % capacity;// 更新frontIndex，循环队列
    count--;// 更新队列中的元素数量
}

template <typename T>
T Queue<T>::front() const// 查看队首元素
{
    if (isEmpty())
    {
        std::cerr << "Queue is empty!" << std::endl;
        throw std::out_of_range("Queue is empty");
    }

    return data[frontIndex];// 返回队首元素
}

template <typename T>
bool Queue<T>::isEmpty() const// 判断队列是否为空
{
    return count == 0;
}

template <typename T>
bool Queue<T>::isFull() const// 判断队列是否已满
{
    return count == capacity;
}

template <typename T>
int Queue<T>::size() const// 返回队列中的元素数量
{
    return count;
}

// Explicit instantiation for common types
template class Queue<int>;
template class Queue<double>;
template class Queue<std::string>;

