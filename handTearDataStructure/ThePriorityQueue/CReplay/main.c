#include <stdio.h>
#include "priority_queue.h"

int main() 
{
    PriorityQueue *pq = createPriorityQueue(10);

    insert(pq, 4, 3);
    insert(pq, 2, 2);
    insert(pq, 5, 1);

    printf("Priority Queue:\n");
    printPriorityQueue(pq);

    printf("\nExtracted Min: %d\n", extractMin(pq));

    printf("\nPriority Queue after extraction:\n");
    printPriorityQueue(pq);

    destroyPriorityQueue(pq);
    return 0;
}



