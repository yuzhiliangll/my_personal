#ifndef __LINKLIST_H_
#define __LINKLIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int // 可以修改为其他数据类型

struct Node
{
    ElementType value; // 存储数据
    struct Node *next; // 指向下一个节点的指针
};

typedef struct Node node;

struct LinkList// 链表结构体
{
    node *head;// 链表头节点指针
    node *tail;  // 链表尾节点指针---希望在链表尾部插入节点时提高效率
    int len;   // 链表长度
};

typedef struct LinkList Llist;

// 链表初始化
void InitLinkList(Llist *list);

// 链表遍历
void TravelLinkList(Llist *list);// 从头结点开始依次访问每个节点--通常用于打印

// 链表尾部插入
bool InsertLinkTail(Llist *list, ElementType element);

// 链表头部插入
bool InsertHead(Llist *list, ElementType element);

// 链表按索引插入
bool InsertByIndex(Llist *list, int index, ElementType element);

// 链表按索引删除
bool RemoveByIndex(Llist *list, int index);

// 链表按值删除
bool RemoveByElement(Llist *list, ElementType element);

// 链表按索引更新
bool UpdateByIndex(Llist *list, int index, ElementType element);

// 链表按值更新
bool UpdateByElement(Llist *list, ElementType oldValue, ElementType newValue);

// 按索引查找元素
ElementType* FindElementByIndex(Llist *list, int index);

// 按值查找元素
int* FindElementByValue(Llist *list, ElementType element);// 查找返回所有匹配指定值的节点的索引

// 判断是否存在指定元素
bool IsHaveElement(Llist *list, ElementType element);

// 判断链表是否为空
bool IsEmpty(Llist *list);

// 链表冒泡排序
void BubbleSort(Llist *list);

// 获取链表交集
Llist GetInsection(Llist *list1, Llist *list2);// 交集中的元素顺序可以不保留

// 获取链表并集
void Deduplicate(Llist *list);// 去重
Llist GetUnionSet(Llist *list1, Llist *list2);// 包含两个链表的所有元素，去重后形成新的链表

// 合并两个链表
Llist Merge(Llist *list1, Llist *list2);// 添加到list1 的尾部形成新的链表

// 链表反转
bool Reserve(Llist *list);

// 链表递归反转
node* ReserveRecursion(node *n); // 通过递归方式, 返回新的头节点

// 释放链表
void FreeLinkList(Llist *list);// 释放链表中的所有节点

// 链表长度
int GetLength(Llist *list);



#endif // __LINKLIST_H_