#include <iostream>
/*
    选择排序（Selection Sort）是一种简单直观的排序算法。
    它的基本思想是每一趟从待排序的数据元素中选出最小（或最大）的一个元素，
    顺序放在已排好序的数列的末尾，直到全部待排序的数据元素排完。

    选择排序算法步骤

    初始状态：未排序的数组。
    选择最小元素：从未排序部分中找到最小（或最大）的元素。
    交换位置：将这个最小元素与未排序部分的第一个元素交换位置。
    标记排序完成：将交换后的第一个元素标记为已排序。
    重复步骤：对剩下的未排序部分重复上述步骤，直到所有元素都已排序。
    
    选择排序的时间复杂度
    最好情况：O(n²)
    最坏情况：O(n²)
    平均情况：O(n²)
    选择排序的代码示例

    选择排序的优缺点
    优点：

    简单直观，容易理解和实现。
    对于小规模数据集，表现尚可。
    缺点：

    时间复杂度较高，效率低下，不适合大规模数据集。
    非稳定排序算法（即相等元素的顺序可能在排序过程中改变）。
*/
#include <vector>

// myswap
void myswap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}


// 选择排序函数
void selectionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)// i表示当前已排序部分的末尾，即每次循环结束后,arr[0...i]是排序好的的部分
    {
        // 假设当前的i是最小值的索引
        int minIndex = i;
        // 找到从i到结尾的最小值
        for (int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;// 更新最小值索引
            }
        }
        // 交换最小值和i位置的值
        std::swap(arr[i], arr[minIndex]);
    }
}
// 打印数组函数
void printArray(const std::vector<int>& arr) 
{
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
int main() 
{
    // 示例数组
    std::vector<int> arr = {64, 25, 12, 22, 11};
    std::cout << "排序前的数组: ";
    printArray(arr);

    // 调用选择排序
    selectionSort(arr);

    std::cout << "排序后的数组: ";
    printArray(arr);

    return 0;
}


