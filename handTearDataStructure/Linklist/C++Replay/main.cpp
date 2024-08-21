#include "LinkList.h"
#include <iostream>

int main() {
    // 创建一个整数类型的链表
    LinkList<int> list;

    // 初始化链表
    list.InitLinkList();

    // 向链表头部插入元素
    list.InsertHead(10);
    list.InsertHead(20);
    list.InsertHead(30);

    // 向链表尾部插入元素
    list.InsertLinkTail(40);
    list.InsertLinkTail(50);

    // 打印链表
    std::cout << "链表内容：" << std::endl;
    list.TravelLinkList();

    // 链表长度
    std::cout << "链表长度: " << list.GetLength() << std::endl;

    // 按索引插入
    list.InsertByIndex(2, 25);
    std::cout << "在索引2插入25后：" << std::endl;
    list.TravelLinkList();

    // 按值删除元素
    list.RemoveByElement(40);
    std::cout << "删除值为40的节点后：" << std::endl;
    list.TravelLinkList();

    // 按索引删除元素
    list.RemoveByIndex(1);
    std::cout << "删除索引为1的节点后：" << std::endl;
    list.TravelLinkList();

    // 按索引查找元素
    int* foundElement = list.FindElementByIndex(2);
    if (foundElement) {
        std::cout << "索引2处的元素值: " << *foundElement << std::endl;
    } else {
        std::cout << "未找到索引2处的元素。" << std::endl;
    }

    // 判断链表中是否存在某个元素
    bool exists = list.IsHaveElement(25);
    std::cout << "链表中是否存在25: " << (exists ? "是" : "否") << std::endl;

    // 链表反转
    list.Reverse();
    std::cout << "链表反转后：" << std::endl;
    list.TravelLinkList();

    // 链表排序
    list.BubbleSort();
    std::cout << "链表排序后：" << std::endl;
    list.TravelLinkList();

    // 释放链表
    list.FreeLinkList();
    std::cout << "释放链表后，链表长度: " << list.GetLength() << std::endl;

    return 0;
}




