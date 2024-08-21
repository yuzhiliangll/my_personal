#include <stdio.h>
#include "Stack.h"

void TestStack() {
    Stack stack;
    InitStack(&stack);

    printf("Pushing elements onto stack...\n");
    Push(&stack, (ElementType)1);
    Push(&stack, (ElementType)2);
    Push(&stack, (ElementType)3);

    printf("Stack after pushes:\n");
    while (!IsStackEmpty(&stack)) {
        printf("%d\n", (int)Peek(&stack)); // 确保元素类型正确
        Pop(&stack);
    }

    // 测试栈的其他功能
    printf("Peek top element: %d\n", (int)Peek(&stack));
    printf("Pop top element: %d\n", (int)Pop(&stack));

    ClearStack(&stack);
    printf("Stack after clear:\n");
    if (IsStackEmpty(&stack)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack is not empty\n");
    }
}

int main() {
    TestStack();
    return 0;
}
