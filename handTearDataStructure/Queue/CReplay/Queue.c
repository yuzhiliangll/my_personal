#include "Queue.h"

// 初始化队列
void InitQueue(Queue *queue) 
{
    InitDLlist(queue);
}

// 入队(尾插法)
void Enqueue(Queue *queue, ElementType element)
{
    InsertDLlistTail(queue, element);
}

// 出队(头删法)
ElementType Dequeue(Queue *queue)
{
    if (IsQueueEmpty(queue))
    {
        perror("Queue is empty");
        return NULL;
    }
    ElementType element = GetDLlistHead(queue)->value;// 获得头节点的值
    RemoveByIndex(queue, 0);// 删除头节点
    return element;// 返回头节点的值
}

// 获取队首元素
ElementType PeekQueue(Queue *queue)
{
    if (IsQueueEmpty(queue))
    {
        perror("Queue is empty");
        return NULL;
    }
    return GetDLlistHead(queue)->value;// 获得头节点的值
}

// 判断队列是否为空
bool IsQueueEmpty(Queue *queue)
{
    return IsEmpty(queue);
}

// 获取队列长度
int GetQueueLength(Queue *queue)
{
    return GetDLlistLength(queue);
}

// 释放队列
void FreeQueue(Queue *queue, void (*funcptr)(ElementType))
{
    FreeDLlist(queue, funcptr);
}

