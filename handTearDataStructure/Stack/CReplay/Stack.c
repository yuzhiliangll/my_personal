#include "Stack.h"

// 初始化栈
void InitStack(Stack *stack) {
    InitDLlist(stack);
}

// 压栈
void Push(Stack *stack, ElementType element) {
    InsertDLlistHead(stack, element); // 栈顶插入新元素--头插法
}

// 弹栈 并返回弹出的元素 -- 栈的核心操作
ElementType Pop(Stack *stack) {
    if (IsStackEmpty(stack)) {
        perror("Stack is empty");
        return NULL; // 或者其他错误处理
    }
    node *top = GetDLlistHead(stack);// 获取栈顶元素--也就是头节点
    ElementType value = top->value;// 
    RemoveByIndex(stack, 0); // 从头部移除
    return value;
}

// 查看栈顶元素
ElementType Peek(Stack *stack) {
    if (IsStackEmpty(stack)) {
        perror("Stack is empty");
        return NULL; // 或者其他错误处理
    }
    return GetDLlistHead(stack)->value;
}

// 判断栈是否为空
bool IsStackEmpty(Stack *stack) {
    return IsEmpty(stack);
}

// 清空栈
void ClearStack(Stack *stack) {
    ClearDLlist(stack); // 使用链表的清空功能
}
