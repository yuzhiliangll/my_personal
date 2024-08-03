#include <iostream>
#include <vector>
#include <algorithm> // for max

/* 示例： 固定大小的滑动窗口 
    假设我们有一个整数数组, 要求找到长度为k 的子数组的最大和
*/
#if 0
// 查找长度为 k 的子数组的最大和
int maxSumSubarray(const std::vector<int>& arr, int k)
{
    int n = arr.size();
    if(n < k) return -1;// 数组长度小于k，返回-1

    // 计算第一个窗口的和
    int max_sum = 0;
    for(int i = 0; i < k; i++)
    {
        max_sum += arr[i];
    }

    int window_sum = max_sum;
    // 滑动窗口,从数组的第k个元素开始
    for(int i = k; i < n; i++)//每次迭代，窗口向右滑动一个位置，即去掉窗口最左边的元素并加上窗口右边的新元素。
    {
        window_sum = window_sum - arr[i - k] + arr[i];
        max_sum = std::max(max_sum, window_sum);//更新最大和：
    }
    return max_sum;
}
/*
    假设我们有一个数组 arr = [1, 2, 3, 4, 5]，窗口大小 k = 3：

计算第一个窗口的和（[1, 2, 3]）：

max_sum = 1 + 2 + 3 = 6
window_sum = 6
滑动窗口，移除 1，加上 4：

window_sum = 6 - 1 + 4 = 9
更新 max_sum 为 9
再次滑动窗口，移除 2，加上 5：

window_sum = 9 - 2 + 5 = 12
更新 max_sum 为 12
*/

int main(int agrc, char* argv[])
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;

    int result = maxSumSubarray(data, k);

    if (result != -1) 
    {
        std::cout << "Maximum sum of subarray of length " << k << " is " << result << std::endl;
    } 
    else {
        std::cout << "Array length is smaller than " << k << std::endl;
    }

    return 0;
}
#endif

/* 例：可变大小的滑动窗口
假设我们有一个正整数数组，要求找到和至少为 S 的最小子数组长度。
*/

#include <climits> // for INT_MAX

int minSubArrayLen(int S, const std::vector<int>& arr)
{
    int n = arr.size();
    int min_len = INT_MAX;//用于存储找到的最小子数组长度，初始值设为 INT_MAX 表示无限大。
    int left = 0;//滑动窗口的左边界
    int sum = 0;//当前窗口的元素和
    for (int right = 0; right < n; right++)//右边界扩展：通过遍历数组，right 指针从左到右移动，扩展窗口的右边界，并将当前元素 arr[right] 加到 sum 中。
    {
        sum += arr[right];
        //检查当前窗口和：如果当前窗口的和 sum 大于或等于目标和 S，我们需要收缩窗口以尝试找到更小的满足条件的子数组。
        while(sum >= S)
        {
            //比较当前窗口长度 right - left + 1 和已知的最小长度 min_len，并更新 min_len 为两者中的较小值。
            min_len = std::min(min_len, right - left + 1);

            //减去 left 指针指向的元素值 arr[left]，并将 left 右移一位，收缩窗口。
            sum -= arr[left];
            left++;
        }
    }

    return (min_len == INT_MAX) ? 0 : min_len;
}
int main() 
{
    std::vector<int> data = {2, 3, 1, 2, 4, 3};
    int S = 7;

    int result = minSubArrayLen(S, data);

    if (result != 0) 
    {
        std::cout << "Minimum length of subarray with sum at least " << S << " is " << result << std::endl;
    } 
    else 
    {
        std::cout << "No subarray with sum at least " << S << std::endl;
    }

    return 0;
}
