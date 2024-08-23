#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <stdexcept>             // std::out_of_range

template <typename T>
class Heap
{
public:
    Heap(bool isMinHeap = true); // default is min heap
    void insert(const T& value); // insert a value to the heap
    T extract();                 // extract the top value from the heap
    const T& top() const;        // return the top value of the heap
    bool isEmpty() const;        // return true if the heap is empty
    int size() const;            // return the size of the heap
    void clear();                // clear the heap
    void print() const;          // print the heap
    void printTree() const;      // print the heap as a tree



private:
    std::vector<T> data;
    bool isMinHeap;

    void heapifyUp(int index);                 // heapify up from a given index
    void heapifyDown(int index);               // heapify down from a given index
    int parent(int index) const;               // return the parent index of a given index
    int leftChild(int index) const;            // return the left child index of a given index
    int rightChild(int index) const;           // return the right child index of a given index
    bool compare(const T& a, const T& b) const;// compare two values

};

#include <iostream>
#include <iomanip>  // std::setw

template <typename T>
Heap<T>::Heap(bool isMinHeap) : isMinHeap(isMinHeap) {} // constructor

template <typename T>
void Heap<T>::insert(const T& value)
{
    data.push_back(value);// add the value to the end of the vector
    heapifyUp(data.size() - 1);// heapify up from the last index
}

/*
    用于从堆中提取(删除并返回) 堆顶元素
    通常为最大堆的最大值或最小堆的最小值
*/
template <typename T>
T Heap<T>::extract()
{
    if (isEmpty())
    {
        throw std::out_of_range("Heap is empty");// throw an exception if the heap is empty
    }

    T root = data.front();// get the root value
    data.front() = data.back();// replace the root value with the last value in the vector
    data.pop_back();// remove the last value from the vector

    // 重新调整堆
    heapifyDown(0);// heapify down from the root index
    return root;// return the root value
}

template <typename T>
const T& Heap<T>::top() const
{
    if (isEmpty())
    {
        throw std::out_of_range("Heap is empty");// throw an exception if the heap is empty
    }

    return data.front();// return the root value
}

template <typename T>
bool Heap<T>::isEmpty() const
{
    return data.empty();// return true if the vector is empty
}

template <typename T>
int Heap<T>::size() const
{
    return data.size();// return the size of the vector
}

template <typename T>
void Heap<T>::clear()
{
    data.clear();// clear the vector
}

template <typename T>
void Heap<T>::print() const
{
    for(const T& element : data)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Heap<T>::printTree() const // 以层次打印堆 -- 显示堆的树形结构
{
    // 计算堆的层数
    /*
        堆是一个完全二叉树，元素的总数是 size()。
        通过不断将 count 除以 2 并增加 levels，我们可以确定树的层数。
    */
    // 即每一层包含的节点数是上一层节点数的两倍
    int levels = 0;
    int count = size();
    while(count > 0)
    {
        count /= 2;
        levels++;
    }

    // 计算最大宽度 -- 确保对齐
    //  计算的是最后一层节点的数量，乘以2表示总的宽度
    int maxWidth = (1 << (levels - 1)) * 2;

    // 打印每一层的节点
    for (int i = 0, level = 0; i < size(); level++) 
    {
        int levelCount = 1 << level; // 计算当前层的节点数
        int spacing = maxWidth / (levelCount + 1);// 当前层中节点之间的间隔
        
        // 内层循环：逐个打印当前层的节点。
        for (int j = 0; j < levelCount && i < size(); j++, i++) 
        {
            std::cout << std::setw(spacing) << "" << data[i];
        }
        std::cout << std::endl;
    }
}

/*
    在插入新元素后，从该元素的当前位置开始，向上调整，直到满足堆的性质为止。
    具体来说，它通过将新插入的元素与其父节点进行比较，
    如果不满足堆的性质（例如：对于最大堆，子节点比父节点大；对于最小堆，子节点比父节点小），则交换它们的位置，继续向上调整。
*/
template <typename T>
void Heap<T>::heapifyUp(int index) // 上浮操作
{
    while (index > 0) // 这个循环一直执行到 index 到达堆的根节点（根节点的索引是 0）为止
    {
        int parentIndex = parent(index);// 获取父节点的索引
        /*
            如果是最大堆，compare 通常是检查 data[index] > data[parentIdx]。
            如果是最小堆，compare 通常是检查 data[index] < data[parentIdx]。
        */
        if (compare(data[index], data[parentIndex])) // 如果当前节点小于父节点
        {
            std::swap(data[index], data[parentIndex]);
            index = parentIndex;
        } 
        else 
        {
            break;
        }
    }
}


/*
    用于在删除堆顶元素后，维护堆的性质。
    它通过从根节点开始，不断向下比较和交换节点，确保堆的顺序性
*/
template <typename T>
void Heap<T>::heapifyDown(int index)
{
    while (true)
    {
        int left = leftChild(index);// 获取左子节点的索引
        int right = rightChild(index);// 获取右子节点的索引
        int smallestOrLargest = index; // 用于跟踪当前节点与其子节点中最大（或最小）的节点索引。

        if (left < size() && compare(data[left], data[smallestOrLargest])) // 如果左子节点存在且小于当前节点
        {
            smallestOrLargest = left; // 更新最小或最大的节点索引为左子节点
        }

        if (right < size() && compare(data[right], data[smallestOrLargest])) // 如果右子节点存在且小于当前节点
        {
            smallestOrLargest = right; // 更新最小或最大的节点索引为右子节点
        }

        if (smallestOrLargest != index) // 如果最小或最大的节点不是当前节点
        {
            std::swap(data[index], data[smallestOrLargest]); // 交换当前节点和最小或最大的节点
            index = smallestOrLargest; // 更新当前节点的索引为最小或最大的节点
        }
        else
        {
            break;
        }
    }
}



template <typename T>
int Heap<T>::parent(int index) const 
{
    return (index - 1) / 2;
}

template <typename T>
int Heap<T>::leftChild(int index) const 
{
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::rightChild(int index) const 
{
    return 2 * index + 2;
}

template <typename T>
bool Heap<T>::compare(const T& a, const T& b) const 
{
    return isMinHeap ? a < b : a > b;
}

// Explicit template instantiation
template class Heap<int>;
template class Heap<double>;
template class Heap<std::string>;


#endif // __HEAP_H__