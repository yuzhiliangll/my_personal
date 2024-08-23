#ifndef __HEAP_H__
#define __HEAP_H__


#include <stdbool.h>

typedef enum // 堆类型
{
    MIN_HEAP,
    MAX_HEAP
}HeapType;

typedef struct 
{
    int* data; // 堆数据
    int size; // 堆大小
    int capacity; // 堆容量
    HeapType type; // 堆类型

}Heap;


// Function prototypes
Heap* createHeap(int capacity, HeapType type);// 创建堆

void insert(Heap* heap, int value);// 插入元素

int extract(Heap* heap);// 提取堆顶元素

int top(const Heap* heap);// 获取堆顶元素

bool isEmpty(const Heap* heap);// 判断堆是否为空

int size(const Heap* heap);// 获取堆的大小

void clear(Heap* heap);// 清空堆

void destroyHeap(Heap* heap);// 销毁堆

void printHeap(const Heap* heap);// 打印堆


#endif // __HEAP_H__