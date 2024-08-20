// #include "DynamicArray.h"
// #include <stdexcept> // 该头文件定义了一组标准异常类

// /*
//     以下是 <stdexcept> 中定义的一些常见异常类：

//     std::logic_error：用于表示程序逻辑中的错误，比如违反了某些前提条件。
//     std::runtime_error：用于表示程序执行过程中的错误，比如在运行时发生的异常情况。
// */

// template <typename T> // 初始化列表--提高效率
// DynamicArray<T>::DynamicArray() : data(nullptr), capacity(0), size(0)
// {
//     // 可以在这里赋初值
//     // this->size = 0;
//     // this->capacity = 10;
//     // this->data = new T[this->capacity];
// }

// template <typename T>
// DynamicArray<T>::~DynamicArray()
// {
//     delete[] data;
// }

// // 动态扩容
// template <typename T>
// void DynamicArray<T>::resize(size_t newCapacity)
// {
//     T* newData = new T[newCapacity];// newData指向新分配的内存空间
//     for (size_t i = 0; i < size; ++i)
//     {
//         newData[i] = data[i];// 将旧数组中的元素复制到新数组中
//     }
//     delete[] data;// 释放旧数组的内存空间
//     data = newData;// 将data指向新分配的内存空间
//     capacity = newCapacity;// 更新capacity
// }

// template <typename T>// 尾插效率高
// void DynamicArray<T>::push_back(const T& value)
// {
//     if (size == capacity)// 如果当前容量已满，则扩容
//     {
//         size_t newCapacity = capacity == 0 ? 1 : capacity * 2;// 计算新容量
//         resize(newCapacity);// 调用resize函数进行扩容
//     }
//     data[size++] = value; // 将元素添加到数组末尾，并更新size
//     // size++;
// }

// // 尾删
// template <typename T>
// void DynamicArray<T>::pop_back()
// {
//     if(size > 0)
//     {
//         --size;// 更新size
//     }
//     else
//     {
//         throw std::out_of_range("Array is empty");
//     }
// }

// // 重载下标运算符
// template <typename T>
// T& DynamicArray<T>::operator[](size_t index)
// {
//     if(index >= size)
//     {
//         throw std::out_of_range("Index out of range");
//     }
//     return data[index];
// }

// // 返回当前数组大小
// template <typename T>
// size_t DynamicArray<T>::getSize() const
// {
//     return size;
// }

// // 返回当前数组容量
// template <typename T>
// size_t DynamicArray<T>::getCapacity() const
// {
//     return capacity;
// }

// // 返回数组是否为空
// template <typename T>
// bool DynamicArray<T>::isEmpty() const
// {
//     return size == 0;
// }

// // 清楚数组
// template <typename T>
// void DynamicArray<T>::clear()
// {
//     delete[] data;
//     data = nullptr;
//     size = 0;
//     capacity = 0;
// }

// // 在指定位置插
// template <typename T>
// void DynamicArray<T>::insert(size_t index, const T& value)
// {
//     if(index > size)// 插入位置大于数组大小
//     {
//         throw std::out_of_range("Index out of range");
//     }

//     if (size == capacity)
//     {
//         resize(capacity == 0 ? 1 : capacity * 2);// 扩容
//     }

//     for (size_t i = size; i > index; i--)
//     {
//         data[i] = data[i - 1];// 向后移动元素
//     }
//     data[index] = value;// 插入元素
//     ++size;// 更新
// }

// template <typename T>
// void DynamicArray<T>::erase(size_t index)
// {
//     if (index >= size)// 删除位置大于等于数组大小
//     {
//         throw std::out_of_range("Index out of range");
//     }

//     // 该位置后的所有元素会向前移动一位以填补空缺
//     for (size_t i = index; i < size - 1; i++)
//     {
//         data[i] = data[i + 1];// 向前移动元素
//     }
//     --size;// 更新
// }
