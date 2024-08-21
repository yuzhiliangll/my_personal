#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "DoubleLinkList.h"

typedef DLlist Queue;// 使用双向链表作为队列的基础结构 -- 先进先出

// 初始化队列
void InitQueue(Queue *queue);

// 入队(尾插法)
void Enqueue(Queue *queue, ElementType element);

// 出队(头删法)
ElementType Dequeue(Queue *queue);

// 获取队首元素
ElementType PeekQueue(Queue *queue);

// 判断队列是否为空
bool IsQueueEmpty(Queue *queue);

// 获取队列长度
int GetQueueLength(Queue *queue);

// 释放队列
void FreeQueue(Queue *queue, void (*funcptr)(ElementType));


#endif // __QUEUE_H__