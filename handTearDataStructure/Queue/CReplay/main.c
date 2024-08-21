#include "Queue.h"
#include <stdio.h>

void printInt(ElementType element)
{
    printf("%d\n", *(int *)element);// element is a pointer to int
}

int main() 
{
    Queue queue;
    InitQueue(&queue);

    int a = 1, b = 2, c = 3;
    Enqueue(&queue, &a);
    Enqueue(&queue, &b);
    Enqueue(&queue, &c);

    printf("Queue Length: %d\n", GetQueueLength(&queue));
    printf("Dequeue: %d\n", *(int *)Dequeue(&queue));
    printf("Peek: %d\n", *(int *)PeekQueue(&queue));
    
    FreeQueue(&queue, NULL);

    return 0;
}
