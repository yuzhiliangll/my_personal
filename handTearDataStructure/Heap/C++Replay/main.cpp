#include "heap.h"

int main() {
    // 测试最小堆
    Heap<int, std::greater<int>> minHeap;
    minHeap.Insert(5);
    minHeap.Insert(1);
    minHeap.Insert(6);
    minHeap.Insert(4);
    minHeap.Insert(2);
    minHeap.Show();

    minHeap.RemoveRoot();
    minHeap.Show();

    // 测试最大堆
    Heap<int, std::less<int>> maxHeap;
    int a[] = {5, 2, 1, 6, 2, 9, 10, 8, 4, 12};
    for (int i = 0; i < 10; ++i) {
        maxHeap.Insert(a[i]);
    }
    maxHeap.Show();

    return 0;
}
