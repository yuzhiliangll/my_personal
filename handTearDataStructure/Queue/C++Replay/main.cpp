#include "Queue.h"
#include <iostream>
#include <string>

int main() 
{
    Queue<int> intQueue(5);  // 创建一个大小为5的整数队列

    std::cout << "Enqueuing elements into the queue..." << std::endl;
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    std::cout << "Queue front element: " << intQueue.front() << std::endl;
    std::cout << "Queue size: " << intQueue.size() << std::endl;

    intQueue.dequeue();
    std::cout << "After dequeuing, queue front element: " << intQueue.front() << std::endl;
    std::cout << "Queue size: " << intQueue.size() << std::endl;

    intQueue.dequeue();
    intQueue.dequeue();
    std::cout << "After dequeuing all elements, is the queue empty? " << (intQueue.isEmpty() ? "Yes" : "No") << std::endl;

    // 测试字符串队列
    Queue<std::string> stringQueue;
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");

    std::cout << "String queue front element: " << stringQueue.front() << std::endl;
    stringQueue.dequeue();
    std::cout << "After dequeuing, string queue front element: " << stringQueue.front() << std::endl;

    return 0;
}
