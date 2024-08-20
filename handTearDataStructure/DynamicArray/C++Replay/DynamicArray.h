#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <iostream>

/*
    设计 DynamicArray 类的目的是让这个类成为一个模板类，可以存储任意类型的数据
    DynamicArray 可以在实例化时指定要存储的数据类型，从而使这个类更加通用和灵活。
    模板类在编译时由编译器生成具体类型的实现，这意味着编译器可以检查类型安全性。
    
    提高代码重用性：
    模板类使得相同的逻辑可以应用于不同的数据类型，而无需重复编写代码
*/

template<typename T> 
class DynamicArray
{
private:
    T* data; // 动态数组指针
    size_t capacity; // 动态数组容量
    size_t size; // 动态数组大小

    // 设置为私有 函数，防止外部直接访问
    void resize(size_t newCapacity); // 动态调整数组容量

public:
    DynamicArray(); // 默认构造函数
    ~DynamicArray(); // 析构函数
    void push_back(const T& value); // 在数组末尾添加元素
    void pop_back(); // 移除最后一个元素
    T& operator[](size_t index); // 重载下标运算符，用于访问元素
    size_t getSize() const; // 获取当前元素数目
    size_t getCapacity() const; // 获取当前数组容量
    bool isEmpty() const; // 检查数组是否为空
    void clear(); // 清空数组

    void insert(size_t index, const T& value); // 在指定位置插入元素
    void erase(size_t index); // 移除指定位置删除元素


};


#include <stdexcept> // 该头文件定义了一组标准异常类

/*
    以下是 <stdexcept> 中定义的一些常见异常类：

    std::logic_error：用于表示程序逻辑中的错误，比如违反了某些前提条件。
    std::runtime_error：用于表示程序执行过程中的错误，比如在运行时发生的异常情况。
*/

template <typename T> // 初始化列表--提高效率
DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0)
{
    // 可以在这里赋初值
    // this->size = 0;
    // this->capacity = 10;
    // this->data = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

// 动态扩容
template <typename T>
void DynamicArray<T>::resize(size_t newCapacity)
{
    T* newData = new T[newCapacity];// newData指向新分配的内存空间
    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = data[i];// 将旧数组中的元素复制到新数组中
    }
    delete[] data;// 释放旧数组的内存空间
    data = newData;// 将data指向新分配的内存空间
    capacity = newCapacity;// 更新capacity
}

template <typename T>// 尾插效率高
void DynamicArray<T>::push_back(const T& value)
{
    if (size == capacity)// 如果当前容量已满，则扩容
    {
        size_t newCapacity = capacity == 0 ? 1 : capacity * 2;// 计算新容量
        resize(newCapacity);// 调用resize函数进行扩容
    }
    data[size++] = value; // 将元素添加到数组末尾，并更新size
    // size++;
}

// 尾删
template <typename T>
void DynamicArray<T>::pop_back()
{
    if(size > 0)
    {
        --size;// 更新size
    }
    else
    {
        throw std::out_of_range("Array is empty");
    }
}

// 重载下标运算符
template <typename T>
T& DynamicArray<T>::operator[](size_t index)
{
    if(index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// 返回当前数组大小
template <typename T>
size_t DynamicArray<T>::getSize() const
{
    return size;
}

// 返回当前数组容量
template <typename T>
size_t DynamicArray<T>::getCapacity() const
{
    return capacity;
}

// 返回数组是否为空
template <typename T>
bool DynamicArray<T>::isEmpty() const
{
    return size == 0;
}

// 清楚数组
template <typename T>
void DynamicArray<T>::clear()
{
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

// 在指定位置插
template <typename T>
void DynamicArray<T>::insert(size_t index, const T& value)
{
    if(index > size)// 插入位置大于数组大小
    {
        throw std::out_of_range("Index out of range");
    }

    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);// 扩容
    }

    for (size_t i = size; i > index; i--)
    {
        data[i] = data[i - 1];// 向后移动元素
    }
    data[index] = value;// 插入元素
    ++size;// 更新
}

template <typename T>
void DynamicArray<T>::erase(size_t index)
{
    if (index >= size)// 删除位置大于等于数组大小
    {
        throw std::out_of_range("Index out of range");
    }

    // 该位置后的所有元素会向前移动一位以填补空缺
    for (size_t i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];// 向前移动元素
    }
    --size;// 更新
}


#endif // __DYNAMICARRAY_H__