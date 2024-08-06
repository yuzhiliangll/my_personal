/*
    分而治之（Divide and Conquer）是一种算法设计思想，其核心思想是将一个复杂的问题分成多个较小的、相似的子问题，然后逐个解决这些子问题，最后将子问题的解组合成原问题的解。
    这个方法特别适用于递归问题，能够有效地减少问题的复杂度，提高算法的效率。

    具体步骤如下：

    分解（Divide）： 将原问题分解成多个规模较小的子问题。这些子问题应该是原问题的子集，且结构上与原问题相似。

    解决（Conquer）： 递归地解决这些子问题。当子问题足够小或简单时，直接解决（即基础情况）。

    合并（Combine）： 将子问题的解合并，得到原问题的解。

    例子
一个经典的分而治之算法例子是归并排序（Merge Sort）。它的步骤如下：

    分解： 将待排序数组分成两半，分别排序。
    解决： 递归地对每一半进行归并排序。
    合并： 将两半排序后的结果合并，得到最终的排序数组。

*/
#include <iostream>
#include <list>
#include <vector>

// // 用C++编写一个递归函数来计算列表包含的元素数
// int countElements(const std::list<int>& lst)
// {
//     // 基础情况：如果列表为空，返回0
//     if (lst.empty())
//     {
//         return 0;
//     }
//     else
//     {
//         // 创建一个新的列表，移除第一个元素
//         std::list<int> sublist(lst);// 递归情况：创建一个新的子列表 sublist，移除第一个元素，然后递归计算子列表的元素数量，并加1。
//         sublist.erase(sublist.begin());
//         // 递归计算子列表的元素数，并加1
//         return 1 + countElements(sublist);// 每次递归调用都会处理一个减少了一个元素的列表，并且加上当前的元素计数 1
//     }
// }
// int main() 
// {
//     std::list<int> myList = {1, 2, 3, 4, 5};
//     int count = countElements(myList);
//     std::cout << "List contains " << count << " elements." << std::endl;
//     return 0;
// }

/*
    下面是一个实现快速排序（Quicksort）算法的 C++ 示例代码。
    快速排序是一种基于分而治之思想的排序算法，具有平均时间复杂度 O(n log n)，

    快速排序的步骤
    选择枢轴（Pivot）： 从数组中选择一个元素作为枢轴。
    分区（Partition）： 重新排序数组，使得所有小于枢轴的元素都位于枢轴的左边，所有大于枢轴的元素都位于枢轴的右边。
    递归排序： 递归地对枢轴左侧和右侧的子数组进行快速排序。
*/
// 分区函数
/*
    partition 函数：

    选择最后一个元素作为枢轴（pivot）。
    遍历数组，确保所有小于枢轴的元素都位于其左侧，大于枢轴的元素位于其右侧。
    最后将枢轴放到正确位置，并返回其索引。
*/
int partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high];// 选择最后一个元素作为枢轴
    int i = (low - 1);// 指向小于枢轴的最后一个元素的位置
    /*
        遍历数组的 low 到 high-1 部分。
        如果当前元素 arr[j] 小于枢轴，则增加 i，并交换 arr[i] 和 arr[j]，将小于枢轴的元素移动到左侧。
    */
    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);// 将小于枢轴的元素移动到左侧
        }
    }
    std::swap(arr[i + 1], arr[high]);// 将枢轴放到正确位置
    return i + 1;// 返回枢轴的索引
}
// 快速排序函数
/*
    递归地调用 partition 函数，将数组分成左右两部分。
    对左右两部分分别进行快速排序。
*/
void quickSort(std::vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);// 获取分区索引
        quickSort(arr, low, pi - 1);// 对枢轴左侧的子数组进行快速排序
        quickSort(arr, pi + 1, high);// 对枢轴右侧的子数组进行快速排序
    }
}
/*
    [10, 7, 8, 9, 1, 5]

    调用 quickSort(arr, 0, 5)
    第一次调用 partition(arr, 0, 5)
    int pivot = arr[high]; // pivot = arr[5] = 5
    int i = low - 1;       // i = 0 - 1 = -1
    遍历数组，将小于 pivot 的元素移到左边：

j = 0: arr[0] = 10, 10 > 5, 不交换。
j = 1: arr[1] = 7, 7 > 5, 不交换。
j = 2: arr[2] = 8, 8 > 5, 不交换。
j = 3: arr[3] = 9, 9 > 5, 不交换。
j = 4: arr[4] = 1, 1 < 5, 交换 arr[0] 和 arr[4]，并将 i 增加 1。

    数组变为：
    [1, 7, 8, 9, 10, 5]
    i = 0
    交换 pivot 和 arr[i+1]：
    [1, 5, 8, 9, 10, 7]
    返回 pivot 的新位置 pi = 1。
*/

int main() 
{
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    std::cout << "Sorted array: \n";
    for (int i = 0; i < n; i++) 
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}




