#include "DynamicArray.h"


int main(int argc, char * argv[])
{
    DynamicArray<int> arr;

    // 测试push_back
    for(int i = 0; i < 10; i++)
    {
        arr.push_back(i);
        std::cout << "Added " << i << "Size: " << arr.getSize() << std::endl;
    }

    // 测试下标访问
    std::cout << "ELement at index 5: " << arr[5] << std::endl;

    // 测试插入元素
    arr.insert(5, 100);
    std::cout << "After insert, element at index 5: " << arr[5] << std::endl;

    // 测试删除元素
    arr.erase(3);
    std::cout << "After erase, element at index 3: " << arr[3] << std::endl;
    std::cout << "Size: " << arr.getSize() << std::endl;
    for(size_t i = 0; i < arr.getSize(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // 测试pop_back
    arr.pop_back();
    std::cout << "After pop_back, size: " << arr.getSize() << std::endl;

    // 测试clear
    arr.clear();
    std::cout << "After clear, size: " << arr.getSize() << ", capacity: " << arr.getCapacity() << std::endl;

    return 0;
}




