#include "Stack.h"
#include <iostream>
#include <string>

int main() 
{
    Stack<int> intStack(5);  // 创建一个大小为5的整数栈

    std::cout << "Pushing elements onto the stack..." << std::endl;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    std::cout << "Stack top element: " << intStack.top() << std::endl;
    std::cout << "Stack size: " << intStack.size() << std::endl;

    intStack.pop();
    std::cout << "After popping, stack top element: " << intStack.top() << std::endl;
    std::cout << "Stack size: " << intStack.size() << std::endl;

    intStack.pop();
    intStack.pop();
    std::cout << "After popping all elements, is the stack empty? " << (intStack.isEmpty() ? "Yes" : "No") << std::endl;

    // 测试字符串栈
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");

    std::cout << "String stack top element: " << stringStack.top() << std::endl;
    stringStack.pop();
    std::cout << "After popping, string stack top element: " << stringStack.top() << std::endl;

    return 0;
}




