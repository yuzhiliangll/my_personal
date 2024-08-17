# ThreadPool-CPP11-async

#### 介绍
一个基于C++11实现的异步线程池，可以根据任务数量动态调节线程池内线程的个数。

#### 代码编译
 - 命令：g++ threadpool.cpp -std=c++11 -lpthread -o app
 - 执行：./app

### 关于编码
如果在Linux下执行提供的代码, 打印的信息可能会出现乱码，这是文件编码造成的，将文件编码修改为 utf8，再次重新编译即可看到正确输出。


#### 关于std::future<int>:

std::future 是 C++11 引入的模板类，提供了一种机制来访问异步操作的结果。std::future<int> 表示一个将来会返回 int 类型结果的对象。
它通常与 std::async、std::promise、或线程池等异步任务相关联。在某个任务提交后，你可以得到一个 std::future 对象，通过这个对象可以查询任务的状态、等待任务完成，以及获取任务的返回结果。

具体用法:

例如，你可能使用 std::async 提交了多个异步任务，每个任务返回一个 int 类型的结果。每次提交任务时，你会得到一个 std::future<int> 对象，你可以把这个对象存储到 results 这个 std::vector 中。
以后你可以遍历这个 results 向量，通过 future 对象的 get() 方法来获取每个任务的执行结果。

```cpp
#include <iostream>
#include <vector>
#include <future>
#include <numeric> // for std::accumulate

int main() {
    std::vector<std::future<int>> results;

    // 异步提交5个任务
    for (int i = 0; i < 5; ++i) {
        results.push_back(std::async(std::launch::async, [i]() {
            return i * i;
        }));
    }

    // 收集每个任务的结果
    for (auto &result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }

    return 0;
}


