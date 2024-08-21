#include "DoubleLinkList.h"
#include <iostream>

// 定义测试函数
void PrintElement(ElementType element) {
    std::cout << *static_cast<int*>(element) << " ";
}

bool CompareElement(ElementType a, ElementType b) {
    return *static_cast<int*>(a) == *static_cast<int*>(b);
}

int main() 
{
    DoubleLinkList list1;
    DoubleLinkList list2;

    // 初始化两个链表
    list1.Init();
    list2.Init();

    // 插入节点
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    list1.InsertTail(&a);
    list1.InsertTail(&b);
    list1.InsertTail(&c);

    list2.InsertTail(&d);
    list2.InsertTail(&e);

    std::cout << "List 1 after insertion: ";
    list1.Travel(PrintElement);
    std::cout << std::endl;

    std::cout << "List 2 after insertion: ";
    list2.Travel(PrintElement);
    std::cout << std::endl;

    // 删除节点
    list1.RemoveByIndex(1); // 删除索引为 1 的节点
    std::cout << "List 1 after removing index 1: ";
    list1.Travel(PrintElement);
    std::cout << std::endl;

    // 更新节点
    int newValue = 10;
    list1.UpdateNodeByIndex(1, &newValue); // 更新索引为 1 的节点
    std::cout << "List 1 after updating index 1: ";
    list1.Travel(PrintElement);
    std::cout << std::endl;

    // 反转链表
    list1.Reverse();
    std::cout << "List 1 after reversing: ";
    list1.Travel(PrintElement);
    std::cout << std::endl;

    // 查找节点
    DoubleLinkList foundList = list1.FindByElement(&newValue, CompareElement);
    std::cout << "List of nodes with value 10: ";
    foundList.Travel(PrintElement);
    std::cout << std::endl;

    // 合并链表
    DoubleLinkList mergedList = list1.Merge(list2);
    std::cout << "Merged list: ";
    mergedList.Travel(PrintElement);
    std::cout << std::endl;

    // 清空链表
    list1.Clear();
    list2.Clear();
    std::cout << "List 1 after clearing: ";
    list1.Travel(PrintElement);
    std::cout << std::endl;

    std::cout << "List 2 after clearing: ";
    list2.Travel(PrintElement);
    std::cout << std::endl;

    // 释放链表
    mergedList.Free(nullptr);
    std::cout << "Merged list after freeing: ";
    mergedList.Travel(PrintElement);
    std::cout << std::endl;

    return 0;
}



