#ifndef __LINKLIST_H__
#define __LINKLIST_H__


#include <iostream>
#include <string>
#include <vector>

template <typename ElementType>
class LinkList
{
private:
    struct Node
    {
        ElementType value;// 存储数据
        Node* next;// 指向下一个节点的指针

        Node(ElementType val) : value(val), next(nullptr) {}// 构造函数
    };

    Node* head;// 指向链表头部的指针
    Node* tail;// 指向链表尾部的指针-- 提高尾部插入效率
    int len;// 链表长度

public:
    LinkList() : head(nullptr), tail(nullptr), len(0) {}// 构造函数

    ~LinkList()// 析构函数
    {
        FreeLinkList();// 释放链表内存
    }

    void FreeLinkList()// 释放链表内存
    {
        Node* current = head;
        while(current != nullptr)
        {
            Node* temp = current;// 保存当前节点
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        len = 0;
    }

    // 链表初始化
    void InitLinkList()
    {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    // 链表遍历
    void TravelLinkList()
    {
        Node* current = head;
        while(current != nullptr)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // 链表尾部插入
    bool InsertLinkTail(const ElementType& element)// const 不可修改
    {
        Node* newNode = new Node(element);
        if (tail)
        {
            tail->next = newNode;// 如果链表不为空，则将新节点插入到尾部

        }
        else
        {
            head = newNode;// 如果链表为空，则将新节点设为头节点
        }
        tail = newNode;// 将新节点设为尾节点
        len++;
        return true;
    }

    // 链表头部插入
    bool InsertHead(const ElementType& element)
    {
        Node* newNode = new Node(element);
        if (head)
        {
            newNode->next = head;// 如果链表不为空，则将新节点插入到头部
        }
        else
        {
            tail = newNode;// 如果链表为空，则将新节点设为尾节点
        }
        head = newNode;// 将新节点设为头节点
        len++;
        return true;
    }

    // 链表按索引插入
    bool InsertByIndex(int index, const ElementType& element)
    {
        if (index < 0 || index > len) return false;// 索引越界
        if (index == 0) return InsertHead(element);// 在头部插入
        if (index == len) return InsertLinkTail(element);// 在尾部插入

        // 中间插入
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;// 找到要插入位置的前一个节点
        }
        Node* newNode = new Node(element);
        newNode->next = current->next;// 将新节点插入到指定位置
        current->next = newNode;
        len++;
        return true;
    }

    // 链表按索引删除
    bool RemoveByIndex(int index)
    {
        // 链表的有效索引范围是 [0, len-1]
        if (index < 0 || index >= len) return false;// 索引越界

        Node* current = head;// 
        if (index == 0)// 删除头节点
        {
            head = head->next;// 将头节点指向下一个节点
            delete current;// 释放原头节点的内存
            if(len == 1) tail = nullptr;// 如果链表只有一个节点，删除后尾节点为空
        }
        else
        {
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;// 找到要删除位置的前一个节点
            }
            Node* temp = current->next;// 保存要删除的节点
            current->next = temp->next;// 将前一个节点指向要删除节点的下一个节点
            if (index == len - 1) tail = current;// 如果删除的是尾节点，更新尾节点
            delete temp;// 释放要删除节点的内存
        }
        len--;
        return true;
    }

    // 链表按值删除
    bool RemoveByElement(const ElementType& element)
    {
        Node* current = head;
        Node* previous = nullptr;

        while(current != nullptr)
        {
            if (current->value == element)
            {
                if (previous)// 不是头节点
                {
                    previous->next = current->next;// 将前一个节点指向当前节点的下一个节点
                    if (current == tail) tail = previous;// 如果删除的是尾节点，更新尾节点
                }
                else// 是头节点
                {
                    head = current->next;// 将头节点指向下一个节点
                    if (current == tail) tail = nullptr;// 如果删除的是尾节点，更新尾节点
                }
                delete current;// 释放当前节点的内存
                len--;
                return true;
            }
            previous = current;// 更新前一个节点
            current = current->next;// 更新当前节点
        }
        return false;
    }

    // 链表按索引更新
    bool UpdateByIndex(int index, const ElementType& element)
    {
        if (index < 0 || index >= len) return false;
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;// 找到要更新的节点
        }
        current->value = element;
        return true;
    }

    // 链表按值更新
    bool UpdateByElement(const ElementType& oldValue, const ElementType& newValue) 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            if (current->value == oldValue) 
            {
                current->value = newValue;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // 按索引查找元素
    ElementType* FindElementByIndex(int index) const
    {
        if (index < 0 || index >= len) return nullptr;
        Node* current = head;// 找到要查找的节点
        for (int i = 0; i < index; i++)
        {
            current = current->next;// 找到要查找的节点
        }
        return &current->value;
    }

    // 按值查找元素
    // 按值查找元素
    std::vector<int> FindElementByValue(const ElementType& element) const 
    {
        std::vector<int> indices;
        Node* current = head;
        int index = 0;
        while (current != nullptr) // 遍历链表
        {
            if (current->value == element) 
            {
                indices.push_back(index);// 将索引添加到向量中
            }
            current = current->next;
            index++;// 索引递增
        }
        return indices;
    }

    // 判断是否存在指定元素
    bool IsHaveElement(const ElementType& element) const 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            if (current->value == element) return true;
            current = current->next;
        }
        return false;
    }

    // 判断链表是否为空
    bool IsEmpty() const 
    {
        return len == 0;
    }

    // 链表冒泡排序
    void BubbleSort() 
    {
        if (len < 2) return;
        for (int i = 0; i < len - 1; ++i) {
            Node* current = head;
            Node* next = current->next;
            for (int j = 0; j < len - 1 - i; ++j) {
                if (current->value > next->value) {
                    std::swap(current->value, next->value);
                }
                current = next;
                next = next->next;
            }
        }
    }

    // 获取链表交集
    LinkList GetIntersection(const LinkList& list2) const 
    {
        LinkList intersection;
        Node* current = head;
        while (current != nullptr) 
        {
            if (list2.IsHaveElement(current->value) && !intersection.IsHaveElement(current->value)) {
                intersection.InsertLinkTail(current->value);
            }
            current = current->next;
        }
        return intersection;
    }

    // 获取链表并集
    void Deduplicate() // 去重
    {
        if (len < 2) return;
        Node* current = head;
        while (current != nullptr) 
        {
            Node* runner = current;
            while (runner->next != nullptr) 
            {
                if (runner->next->value == current->value) 
                {
                    Node* temp = runner->next;
                    runner->next = temp->next;
                    if (temp == tail) tail = runner;
                    delete temp;
                    len--;
                } 
                else 
                {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    LinkList GetUnionSet(const LinkList& list2) const 
    {
        LinkList unionSet = *this;
        Node* current = list2.head;
        while (current != nullptr) 
        {
            if (!unionSet.IsHaveElement(current->value)) 
            {
                unionSet.InsertLinkTail(current->value);
            }
            current = current->next;
        }
        unionSet.Deduplicate();
        return unionSet;
    }

    // 合并两个链表
    LinkList Merge(const LinkList& list2) const 
    {
        LinkList mergedList = *this;// this指向当前对象
        Node* current = list2.head;// list2的头节点
        while (current != nullptr) 
        {
            mergedList.InsertLinkTail(current->value);// 将list2的节点插入到mergedList的尾部
            current = current->next;
        }
        return mergedList;
    }

    // 链表反转
    bool Reverse()
    {
        if (len < 2) return false;// 链表为空或没有节点-- 没必要反转
        Node* prev = nullptr;// 前一个节点
        Node* current = head;// 当前节点
        tail = head;// 反转后头节点变成 尾节点

        while (current != nullptr)
        {
            Node* next = current->next;// 保存下一个节点 -- 因为反转操作会改变 current->next，需要先保存
            current->next = prev;// 将当前节点的next指向前一个节点
            prev = current;// 前一个节点后移
            current = next;// 当前节点后移
        }
        head = prev;// 将头节点指向最后一个节点 --- 也就是新的头节点
        return true;
    }

    // 链表递归反转
    Node* ReverseRecursion(Node* node) 
    {
        if (!node || !node->next) 
        {
            return node;
        }
        Node* newHead = ReverseRecursion(node->next);
        node->next->next = node;
        node->next = nullptr;
        return newHead;
    }

    void ReverseRecursion() 
    {
        head = ReverseRecursion(head);
    }

    // 释放链表 -- 在上面

    // 链表长度
    int GetLength() const
    {
        return len;
    }

};

/*
    关于链表的反转
    初始化三个指针：prev、current 和 tail。
    Node* prev = nullptr; // 前一个节点
    Node* current = head; // 当前节点
    tail = head;          // tail 指向反转前的头节点
        prev：用于跟踪前一个节点，初始为 nullptr。
        current：用于跟踪当前节点，初始为链表的头节点 head。
        tail：指向链表的原始头节点，因为反转后它将成为新的尾节点。

    while (current != nullptr) 
    {
    Node* next = current->next; // 保存当前节点的下一个节点
    current->next = prev;       // 将当前节点的 next 指向前一个节点（反转）
    prev = current;             // 将 prev 后移到当前节点
    current = next;             // 将 current 后移到下一个节点   
    }
    这个循环持续进行，直到 current 变为 nullptr，表示已经遍历完链表。

    循环结束后，原链表的最后一个节点（即 prev）成为新的头节点--head = prev;


*/

#endif // __LINKLIST_H__