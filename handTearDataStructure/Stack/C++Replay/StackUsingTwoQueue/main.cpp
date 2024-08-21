#include "StackUsingTwoQueues.h"
#include <iostream>

int main() {
    StackUsingTwoQueues<int> stack;

    // 测试入栈操作
    std::cout << "Pushing elements onto the stack..." << std::endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 测试栈顶元素
    std::cout << "Top element: " << stack.top() << std::endl;

    // 测试出栈操作
    stack.pop();
    std::cout << "After popping, top element: " << stack.top() << std::endl;

    // 测试出栈到空栈
    stack.pop();
    stack.pop();
    try {
        stack.top(); // 应该抛出异常
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Is the stack empty? " << (stack.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}



