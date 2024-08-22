#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <vector> // for vector
#include <functional>// for std::greater

template<typename T, typename Compare = std::less<T>>
class Heap
{
public:
    Heap() = default;// default constructor

    void Insert(T value)
    {
        array.push_back(value);
        SiftUp(array.size() - 1);// 从最后一个节点开始向上调整
    }

    void RemoveRoot()
    {
        if (array.empty())// if the array is empty
            return;

        array[0] = array.back();// 将最后一个元素放到根节点
        array.pop_back();// 删除最后一个元素
        SiftDown(0);// 从根节点开始向下调整
    }

    T GetRoot() const// 获得根节点
    {
        if (array.empty())
            throw std::out_of_range("Heap is empty");

        return array[0];
    }

    bool Search(const T& value) const// 查找元素
    {
        for (const auto& elem : array)
        {
            if (elem == value)
                return true;
        }

        return false;
    }

    void Show() const// 打印堆
    {
        for (const auto& elem : array)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> array;
    Compare compare;// for compare

    int GetParent(int i) const { return (i - 1) / 2; } // 获得父节点
    int GetLeftChild(int i) const { return 2 * i + 1; } // 获得左子节点
    int GetRightChild(int i) const { return 2 * i + 2; } // 获得右子节点

    // 上浮操作
    void SiftUp(int i)
    {
        while (i > 0 && compare(array[i], array[GetParent(i)]))// 如果当前节点比父节点小（最小堆），则交换
        {
            std::swap(array[i], array[GetParent(i)]);
            i = GetParent(i);// 更新当前节点
        }
    }

    // 下沉操作
    void SiftDown(int i)
    {
        int leftChild = GetLeftChild(i);// 获得左子节点
        int rightChild = GetRightChild(i);// 获得右子节点

        int target = i;

        if (leftChild < array.size() && compare(array[leftChild], array[target]))// 如果左子节点比当前节点小（最小堆），则更新目标节点
        {
            target = leftChild;
        }

        if (rightChild < array.size() && compare(array[rightChild], array[target]))// 如果右子节点比当前节点小（最小堆），则更新目标节点
        {
            target = rightChild;
        }

        if (target != i)// 如果目标节点不是当前节点，则交换
        {
            std::swap(array[i], array[target]);
            SiftDown(target);// 递归调用下沉操作
        }
    }
};

#endif // __HEAP_H
