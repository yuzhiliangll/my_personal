/*
    在 C++ 中，使用标准库中的 std::priority_queue 可以很方便地实现优先级队列。std::priority_queue 是一个容器适配器，它通常基于最大堆（最大优先级队列），但你可以通过自定义比较器来实现最小堆（最小优先级队列）。

    使用 std::priority_queue
    下面是一个使用 std::priority_queue 的基本示例：

    1. 最大优先级队列（默认）
    默认情况下，std::priority_queue 使用最大堆，因此具有最高优先级的元素会被优先处理。
*/
#if 0
#include <iostream>
#include <queue>

int main() {
    // 创建一个最大优先级队列
    std::priority_queue<int> pq;

    // 插入元素
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);

    // 输出并移除最高优先级的元素
    while (!pq.empty()) {
        std::cout << pq.top() << std::endl; // 打印最高优先级的元素
        pq.pop(); // 移除最高优先级的元素
    }
    /*
        在这个示例中，pq.top() 用于获取当前队列中优先级最高的元素，
        pq.pop() 用于移除该元素。
        输出结果将是从大到小的顺序：20, 15, 10, 5。
    */

    return 0;
}
#endif
/*
    2. 最小优先级队列
    要实现最小优先级队列，可以使用自定义比较器。这里我们使用 std::greater<int> 作为比较器，
    这样 std::priority_queue 会变成一个最小堆。
*/

#include <iostream>
#include <queue>
#include <vector>
#include <functional> // For std::greater

int main() {
    // 创建一个最小优先级队列
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    // 插入元素
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(15);

    // 输出并移除最低优先级的元素
    while (!pq.empty()) {
        std::cout << pq.top() << std::endl; // 打印最低优先级的元素
        pq.pop(); // 移除最低优先级的元素
    }
    /*
        在这个示例中，std::greater<int> 比较器使得优先级队列变成一个最小堆，
        从小到大的顺序输出：5, 10, 15, 20。
    */

    return 0;
}





