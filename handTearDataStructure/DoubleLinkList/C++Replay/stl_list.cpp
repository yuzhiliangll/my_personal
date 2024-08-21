/*
    在 C++ 中，与双向链表功能相似的标准容器是 std::list。std::list 是一个双向链表，它提供了以下特性：

    双向链接：每个元素都有指向前一个和下一个元素的指针，因此你可以在链表的两端进行高效的插入和删除操作。
    非连续存储：元素在内存中不是连续存储的，而是分散在不同的内存位置。
    高效的插入和删除：在链表的任意位置插入或删除元素都是 O(1) 时间复杂度（假设你已经有了指向目标位置的迭代器）。
    遍历：你可以从链表的头部或尾部进行前向或后向遍历。
*/
#if 0
#include <iostream>
#include <list>

int main() {
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 插入元素
    myList.push_front(0);   // 在前面插入
    myList.push_back(6);    // 在后面插入

    // 遍历并输出元素
    for (int value : myList) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 删除元素
    myList.pop_front();     // 删除前面元素
    myList.pop_back();      // 删除后面元素

    // 再次遍历并输出元素
    for (int value : myList) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    return 0;
}
#endif

/*

std::list 是 C++ 标准库中的一个双向链表容器，提供了多种功能用于管理和操作链表中的元素。以下是 std::list 的所有功能及使用注意事项：

主要功能
构造和赋值

默认构造：std::list<T> myList;
填充值构造：std::list<T> myList(size, value);，创建一个包含 size 个值为 value 的元素的链表。
范围构造：std::list<T> myList(begin, end);，使用迭代器范围 [begin, end) 初始化链表。
拷贝构造：std::list<T> myList(otherList);，拷贝构造一个链表。
移动构造：std::list<T> myList(std::move(otherList));，使用移动语义构造链表。
元素访问

前向遍历：使用 begin() 和 end() 获取前向迭代器。
后向遍历：使用 rbegin() 和 rend() 获取反向迭代器。
访问第一个元素：front()，返回链表的第一个元素的引用。
访问最后一个元素：back()，返回链表的最后一个元素的引用。
插入和删除

在前面插入：push_front(const T& value)，在链表的前面插入元素。
在后面插入：push_back(const T& value)，在链表的后面插入元素。
在指定位置插入：insert(iterator pos, const T& value)，在 pos 位置之前插入元素。
删除第一个元素：pop_front()，删除链表的第一个元素。
删除最后一个元素：pop_back()，删除链表的最后一个元素。
删除指定元素：erase(iterator pos)，删除链表中 pos 位置的元素。
删除指定范围的元素：erase(iterator first, iterator last)，删除链表中 [first, last) 范围的元素。
清空链表：clear()，删除链表中的所有元素。
操作

排序：sort()，对链表中的元素进行排序。
唯一化：unique()，移除链表中的重复元素（要求链表已排序）。
合并：merge(list& other)，将 other 链表合并到当前链表中（要求两个链表已排序）。
反转：reverse()，反转链表中的元素顺序。
容量

检查是否为空：empty()，检查链表是否为空。
获取大小：size()，返回链表中元素的数量。
比较

比较两个链表：可以使用 ==、!=、<、>、<=、>= 操作符比较两个链表。
使用注意事项
随机访问效率：std::list 不支持随机访问（如 operator[]），因此不能使用下标操作来访问元素。需要使用迭代器来访问元素。

内存开销：由于双向链表需要为每个节点存储额外的指针，因此在内存开销上比 std::vector 要大。

迭代器失效：在插入或删除元素时，只有涉及到链表的当前节点及其邻接节点的迭代器会失效，其它迭代器通常不会失效。

排序和合并：sort 和 merge 操作需要链表中的元素支持 < 运算符（对于 std::list，这两个操作是基于链表内的元素排序）。

高效插入和删除：链表的插入和删除操作是 O(1) 时间复杂度，但前提是你有一个有效的迭代器指向要插入或删除的位置。

避免频繁操作：对于需要频繁进行随机访问的操作，std::list 可能不如 std::vector 或 std::deque 高效。

自定义排序：sort 方法可以接受自定义比较函数来改变排序顺序。例如：myList.sort([](const T& a, const T& b) { return a > b; });。

*/

#include <iostream>
#include <list>
#include <algorithm> // For std::sort

int main() 
{
    // 创建一个 std::list 并初始化
    std::list<int> myList = {5, 2, 9, 1, 5, 6};

    // 打印链表的初始状态
    std::cout << "Initial list: ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 在前面插入元素
    myList.push_front(0);

    // 在后面插入元素
    myList.push_back(10);

    // 打印链表状态
    std::cout << "After push_front(0) and push_back(10): ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 删除第一个元素
    myList.pop_front();

    // 删除最后一个元素
    myList.pop_back();

    // 打印链表状态
    std::cout << "After pop_front() and pop_back(): ";
    for (int value : myList) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 在特定位置插入元素
    auto it = myList.begin();
    std::advance(it, 2); // 移动迭代器到第三个位置
    myList.insert(it, 100);

    // 打印链表状态
    std::cout << "After insert(100) at position 2: ";
    for (int value : myList) {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 删除特定位置的元素
    it = myList.begin();
    std::advance(it, 3); // 移动迭代器到第四个位置
    myList.erase(it);

    // 打印链表状态
    std::cout << "After erase at position 3: ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 排序链表
    myList.sort();

    // 打印排序后的链表
    std::cout << "After sort(): ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 移除重复的元素
    myList.unique();

    // 打印去重后的链表
    std::cout << "After unique(): ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 反转链表
    myList.reverse();

    // 打印反转后的链表
    std::cout << "After reverse(): ";
    for (int value : myList) 
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    // 清空链表
    myList.clear();

    // 打印链表状态
    std::cout << "After clear(): ";
    if (myList.empty()) 
    {
        std::cout << "List is empty" << std::endl;
    } 
    else 
    {
        for (int value : myList) 
        {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}




