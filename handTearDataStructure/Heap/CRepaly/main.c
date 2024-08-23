#include <stdio.h>
#include "heap.h"

int main() 
{
    Heap* minHeap = createHeap(10, MIN_HEAP);
    Heap* maxHeap = createHeap(10, MAX_HEAP);

    // Test min heap
    insert(minHeap, 3);
    insert(minHeap, 1);
    insert(minHeap, 4);
    insert(minHeap, 1);
    insert(minHeap, 5);
    insert(minHeap, 9);

    printf("Min Heap: ");
    printHeap(minHeap);
    printf("Extracted from Min Heap: %d\n", extract(minHeap));
    printf("Min Heap after extraction: ");
    printHeap(minHeap);

    // Test max heap
    insert(maxHeap, 3);
    insert(maxHeap, 1);
    insert(maxHeap, 4);
    insert(maxHeap, 1);
    insert(maxHeap, 5);
    insert(maxHeap, 9);

    printf("Max Heap: ");
    printHeap(maxHeap);
    printf("Extracted from Max Heap: %d\n", extract(maxHeap));
    printf("Max Heap after extraction: ");
    printHeap(maxHeap);

    clear(minHeap);
    clear(maxHeap);

    destroyHeap(minHeap);
    destroyHeap(maxHeap);

    return 0;
}
