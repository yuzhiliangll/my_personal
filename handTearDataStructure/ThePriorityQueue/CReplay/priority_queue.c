#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PARENT(i) ((i - 1) / 2) // parent index
#define LEFT_CHILD(i) (2 * i + 1) // left child index
#define RIGHT_CHILD(i) (2 * i + 2) // right child index

/*
    swap 函数用于交换优先级队列中索引 i 和索引 j 处的元素。
    这样做是为了调整堆的结构，以维护堆的性质。
    它通常在堆的操作中使用，如插入新元素或删除最小元素后。
*/
static void swap(PriorityQueue *pq, int i, int j) // 目的是确保堆的属性（如最小堆的特性）在元素插入或删除后能够保持一致
{
    int tempData = pq->data[i];// 我们声明了两个临时变量 tempData 和 tempPriority，用来暂时保存索引 i 处的元素和优先级。这样可以避免在交换过程中丢失这些值。
    int tempPriority = pq->priority[i];
    pq->data[i] = pq->data[j];
    pq->priority[i] = pq->priority[j];//将索引 j 处的优先级赋给索引 i 处的优先级
    pq->data[j] = tempData;// 将临时保存的 data 和 priority 值赋给索引 j 处
    pq->priority[j] = tempPriority;
}


/*
    heapify 函数用于调整堆的结构，使其满足堆的性质。
    它的作用是调整堆中的一个特定元素的位置，以确保最小堆的特性得到保持。

    功能说明
    heapify 函数用于将堆中从 index 开始的子树调整为一个最小堆。
    它确保堆的根节点是所有子节点中具有最小优先级的节点。


*/
static void heapify(PriorityQueue *pq, int index) 
{
    int smallest = index;// smallest 用于记录当前子树中具有最小优先级的节点的索引。

    // 计算左右子节点的索引
    int left = LEFT_CHILD(index);
    int right = RIGHT_CHILD(index);

    // 比较左子节点和当前节点
    /*
        如果左子节点存在（即 left 小于堆的大小）且其优先级小于当前 smallest 节点的优先级，
        则更新 smallest 为左子节点的索引。
    */
    if (left < pq->size && pq->priority[left] < pq->priority[smallest]) 
    {
        smallest = left;
    }

    // 比较右子节点和当前节点

    if (right < pq->size && pq->priority[right] < pq->priority[smallest]) 
    {
        smallest = right;
    }

    // 如果当前节点的优先级不是最小的，则交换节点并递归调整堆
    if (smallest != index) 
    {
        swap(pq, index, smallest);
        heapify(pq, smallest);
    }
}

PriorityQueue* createPriorityQueue(int capacity) // 创建一个优先级队列
{
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (int*)malloc(capacity * sizeof(int));
    pq->priority = (int*)malloc(capacity * sizeof(int));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void destroyPriorityQueue(PriorityQueue *pq) // 释放优先队列的内存
{
    if (pq) 
    {
        free(pq->data);
        free(pq->priority);
        free(pq);
    }
}

bool insert(PriorityQueue *pq, int item, int priority) 
{
    if (pq->size == pq->capacity) 
    {
        return false; // Queue is full
    }

    int index = pq->size++;
    pq->data[index] = item;
    pq->priority[index] = priority;

    while (index != 0 && pq->priority[PARENT(index)] > pq->priority[index]) 
    {
        swap(pq, index, PARENT(index));
        index = PARENT(index);
    }
    return true;
}

int extractMin(PriorityQueue *pq) // 
{
    if (pq->size <= 0) {
        return INT_MIN; // Queue is empty
    }
    if (pq->size == 1) 
    {
        return pq->data[--pq->size];
    }

    int root = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    pq->priority[0] = pq->priority[pq->size];
    heapify(pq, 0);

    return root;
}

bool isEmpty(PriorityQueue *pq) // check if the queue is empty
{
    return pq->size == 0;
}

bool isFull(PriorityQueue *pq) // check if the queue is full
{
    return pq->size == pq->capacity;
}

void printPriorityQueue(PriorityQueue *pq) // print the queue
{
    for (int i = 0; i < pq->size; i++) 
    {
        printf("Item: %d, Priority: %d\n", pq->data[i], pq->priority[i]);
    }
}


