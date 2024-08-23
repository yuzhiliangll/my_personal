#include <limits.h> // INT_MAX
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>



static void swap(int* a, int* b)// 交换两个元素
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapifyUp(Heap* heap, int index)// 上浮
{
    if (index && (heap->type == MIN_HEAP ? heap->data[index] < heap->data[(index - 1) / 2] : heap->data[index] > heap->data[(index - 1) / 2])) 
    {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        heapifyUp(heap, (index - 1) / 2);
    }
}

static void heapifyDown(Heap* heap, int index)// 下沉
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int extremum = index;

    if (left < heap->size && (heap->type == MIN_HEAP ? heap->data[left] < heap->data[extremum] : heap->data[left] > heap->data[extremum])) 
    {
        extremum = left;
    }

    if (right < heap->size && (heap->type == MIN_HEAP ? heap->data[right] < heap->data[extremum] : heap->data[right] > heap->data[extremum])) {
        extremum = right;
    }

    if (extremum != index) 
    {
        swap(&heap->data[index], &heap->data[extremum]);
        heapifyDown(heap, extremum);
    }
}

Heap* createHeap(int capacity, HeapType type)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap)); // 创建堆
    heap->data = (int*)malloc(capacity * sizeof(int)); // 创建堆的数组
    heap->size = 0;// 当前堆的大小
    heap->type = type;// 堆的类型
    heap->capacity = capacity;// 堆的容量
    return heap;
}

// 插入
void insert(Heap* heap, int value)
{
    if (heap->size == heap->capacity) // 扩容 
    {
        heap->capacity *= 2;// 容量翻倍
        heap->data = (int *)realloc(heap->data, heap->capacity * sizeof(int));// 重新分配内存
    }
    heap->data[heap->size] = value; // 插入元素
    heapifyUp(heap, heap->size++);// 上浮

}

int extract(Heap* heap) 
{
    if (isEmpty(heap)) 
    {
        fprintf(stderr, "Heap is empty\n");
        return INT_MIN; // or another appropriate error value
    }
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size]; // 将最后一个元素放到堆顶
    heapifyDown(heap, 0);// 下沉
    return root;
}

int top(const Heap* heap)
{
    if (isEmpty(heap)) 
    {
        fprintf(stderr, "Heap is empty\n");
        return INT_MIN; // or another appropriate error value
    }
    return heap->data[0];// 返回堆顶元素
}

bool isEmpty(const Heap* heap)
{
    return heap->size == 0;
}

int size(const Heap* heap)
{
    return heap->size;
}

void clear(Heap* heap)
{
    heap->size = 0;// 清空堆
}

void destroyHeap(Heap* heap)
{
    free(heap->data);
    free(heap);
}

void printHeap(const Heap* heap)
{
    for (int i = 0; i < heap->size; i++) 
    {
        printf("%d ", heap->data[i]);// 打印堆中的元素
    }
    printf("\n");
}
