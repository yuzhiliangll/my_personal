#include <iostream>
#include <vector>
#include <algorithm> // for sort

/* 二分查找函数 : 前提是有序 */
/*
    给定一个已排序的整数向量arr和一个目标值target，
    并返回目标值在向量中的索引。如果未找到目标值，则返回-1。
*/
int binarySearch(const std::vector<int>& arr, int target)
{
    // 确定查找范围
    int left = 0;
    int right = arr.size() - 1;
    while(left <= right)
    {
        // 每次检查中间元素
        int mid = left + (right - left) / 2;
        if(arr[mid] == target)
        {
            return mid;
        }
        else if(arr[mid] < target)
        {
            left = mid + 1;
        }
        else if(arr[mid] > target)
        {
            right = mid - 1;
        }

    }
    return -1;// 如果没有找到返回-1
}

int main(int argc, char* argv[])
{
    std::vector<int> data = {5, 3, 8, 6, 2, 10, 7, 1, 9, 4};
    /* 二分查找先排序 */
    std::sort(data.begin(), data.end());
    // 
    std::cout << "Sorted array: ";
    for(int num : data)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    int target = 6;
    int result = binarySearch(data, target);

    if(result != -1)
    {
        std::cout << "Target " << target << " found at index " << result << std::endl;
    }
    else
    {
        std::cout << "Target " << target << " not found in the array." << std::endl;
    }

    return 0;
}
