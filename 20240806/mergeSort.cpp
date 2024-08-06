/*
    归并排序（Merge Sort）是一种基于分而治之思想的排序算法，
    它将数组分成两个子数组，分别对这两个子数组进行排序，然后合并这两个已排序的子数组以得到最终的排序结果。
    归并排序的时间复杂度为 O(n log n)
    
    归并排序的步骤
    分割（Divide）： 将数组从中间分成两个子数组。
    排序（Conquer）： 递归地对每个子数组进行归并排序。
    合并（Combine）： 合并两个已排序的子数组。

*/
/*
    递归版本
*/
#include <iostream>
#include <vector>

// 合并两个已排序的子数组
void merge(std::vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组到原数组
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 拷贝剩余元素
    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
}

// 归并排序函数
void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // 递归排序左半部分
        mergeSort(arr, left, mid);
        // 递归排序右半部分
        mergeSort(arr, mid + 1, right);
        // 合并两个已排序的子数组
        merge(arr, left, mid, right);
    }
}
int main() 
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int arr_size = arr.size();

    std::cout << "Given array is \n";
    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    mergeSort(arr, 0, arr_size - 1);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}

/*
    非递归版本

*/
// 非递归归并排序
void mergeSortIterative(std::vector<int>& arr) 
{
    int n = arr.size();
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) 
    {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) 
        {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}