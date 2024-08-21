#include "QueueUsingTwoStacks.h"
#include <iostream>

int main() {
    QueueUsingTwoStacks<int> queue;

    // 测试入队操作
    std::cout << "Enqueuing elements..." << std::endl;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    // 测试获取队头元素
    std::cout << "Front element: " << queue.peek() << std::endl;

    // 测试出队操作
    queue.pop();
    std::cout << "After dequeuing, front element: " << queue.peek() << std::endl;

    // 测试出队到空队列
    queue.pop();
    queue.pop();
    try {
        queue.peek(); // 应该抛出异常
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
