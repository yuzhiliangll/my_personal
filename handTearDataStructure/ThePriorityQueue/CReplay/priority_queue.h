#ifndef __PRIORITY_QUEUE_H
#define __PRIORITY_QUEUE_H

/*
    在 C 中实现优先级队列（Priority Queue）可以借助堆（Heap）数据结构。
    优先级队列是一种特殊的队列，其中每个元素都有一个优先级，
    元素总是以优先级顺序被处理。常用的实现方式是基于二叉堆（Binary Heap）。
    这里是一个使用最小堆实现的优先级队列的基本示例
*/

#include <stdbool.h>

typedef struct 
{
    int* data;// 存储数据的数组
    int* priority;// 存储优先级的数组
    int capacity;// 队列的容量
    int size;// 当前队列中的元素数量
    
}PriorityQueue;// 优先级队列

PriorityQueue* createPriorityQueue(int capacity);// 创建优先级队列
void destroyPriorityQueue(PriorityQueue *pq);// 销毁优先级队列
bool insert(PriorityQueue *pq, int item, int priority);// 插入元素
int extractMin(PriorityQueue *pq);// 提取优先级最低的元素
bool isEmpty(PriorityQueue *pq);// 检查队列是否为空
bool isFull(PriorityQueue *pq);// 检查队列是否已满
void printPriorityQueue(PriorityQueue *pq);// 打印队列中的元素


#endif //__PRIORITY_QUEUE_H