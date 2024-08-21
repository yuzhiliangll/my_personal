#ifndef __STACK_H__
#define __STACK_H__

#include "DoubleLinkList.h"

// 栈结构体
typedef DLlist Stack;

// 栈初始化
void InitStack(Stack *stack);

// 压栈
void Push(Stack *stack, ElementType element);

// 弹栈
ElementType Pop(Stack *stack);

// 查看栈顶元素
ElementType Peek(Stack *stack);

// 判断栈是否为空
bool IsStackEmpty(Stack *stack);

// 清空栈
void ClearStack(Stack *stack);

#endif //__STACK_H__