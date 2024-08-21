#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef void* ElementType; // ElementType is a pointer to void

struct Node
{
    ElementType value;// value is a pointer to void
    struct Node* next;// next is a pointer to Node
    struct Node* prev;// prev is a pointer to Node
};
typedef struct Node node;// node is a struct Node

struct DoubleLinkList
{
    node *head;
    node *tail;// tail is a pointer to Node
    int len;
};
typedef struct DoubleLinkList DLlist;

// function declaration

void InitDLlist(DLlist *list);// initialize the list

node* CreateNode(ElementType element);// create a node with element

// 尾插
void InsertDLlistTail(DLlist *list, ElementType element);// insert a node with element at the end of the list

// 头插
void InsertDLlistHead(DLlist *list, ElementType element);// insert a node with element at the beginning of the list

// 按索引插入
void InsertByIndex(DLlist *list, int index, ElementType element);

// 新增: 按索引查找节点
node* FindByIndex(DLlist *list, int index);

// 新增: 更新节点值
void UpdateNodeByIndex(DLlist *list, int index, ElementType newValue);

void Travel(DLlist *list, void (*funcptr)(ElementType));

void ReTravel(DLlist *list, void (*funcptr)(ElementType));

// 按索引删除
void RemoveByIndex(DLlist *list, int index);

// 按值删除
void RemoveByElement(DLlist *list, ElementType element, bool (*funcptr)(ElementType, ElementType));

// 释放
void FreeDLlist(DLlist *list, void (*funcptr)(ElementType));

// 新增: 清空链表
void ClearDLlist(DLlist *list);

DLlist FindByElement(DLlist *list, ElementType element, bool (*funcPtr)(ElementType, ElementType));

// 合并链表
DLlist MergeDLlist(DLlist *list1, DLlist *list2);

// 反转链表
void ReverseDLlist(DLlist *list);

// 新增: 判断链表是否为空
bool IsEmpty(DLlist *list);

// 获取链表长度
int GetDLlistLength(DLlist *list);

// 获取头节点
node* GetDLlistHead(DLlist *list);

// 获取尾节点
node* GetDLlistTail(DLlist *list);


#endif //__DOUBLELINKLIST_H__