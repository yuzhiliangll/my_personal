/*
    给定⼀个 n 个元素有序的（升序）整型数组 nums 和⼀个⽬标值 target ，写⼀个函数搜索 nums 中的 target，如
    果⽬标值存在返回下标，否则返回 -1。
    示例 1:
    输⼊: nums = [-1,0,3,5,9,12], target = 9
    输出: 4
    解释: 9 出现在 nums 中并且下标为 4

    输⼊: nums = [-1,0,3,5,9,12], target = 2
    输出: -1
    解释: 2 不存在 nums 中因此返回 -1

*/

/*
    ⼆分查找涉及的很多的边界条件，逻辑⽐较简单，但就是写不好。例如到底是 while(left < right) 还是
    while(left <= right) ，到底是 right = middle 呢，还是要 right = middle - 1 呢？
    ⼤家写⼆分法经常写乱，主要是因为对区间的定义没有想清楚，区间的定义就是不变量。要在⼆分查找的过程中，
    保持不变量，就是在while寻找中每⼀次边界的处理都要坚持根据区间的定义来操作，这就是循环不变量规则。
    写⼆分法，区间的定义⼀般为两种，左闭右闭即[left, right]，或者左闭右开即[left, right)。

*/
#include <iostream>
#include <vector>

// 版本一：左闭右闭区间 [left, right]
class Solution
{
public:
    int search(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1; // 定义在target在左闭右闭的区间里, [left, right]
        while (left <= right) // 当left==right，区间[left, right]依然有效
        {
            int middle = left + ((right - left) / 2);// 防止溢出, 等同于 (left + right) / 2 
            if(nums[middle] > target)
            {
                right = middle - 1; // target 在左区间, 所以[left, middle - 1]
            }
            else if(nums[middle] < target)
            {
                left = middle + 1; //  target 在右区间, 所以[middle + 1, right]
            }
            else
            {
                // nums[middle] == target
                return middle; // 找到target，直接返回 下标
            }
        }

        // 未找到目标值
        return -1;
    }
};
/*
    时间复杂度为: O(logn)
    空间复杂度为: O(1)
*/

/*
    二分法第二种写法
    版本二：左闭右开区间
        如果说定义 target 是在⼀个在左闭右开的区间⾥，也就是[left, right) ，那么⼆分法的边界处理⽅式则截然不同。
        有如下两点：
        while (left < right)，这⾥使⽤ < ,因为left == right在区间[left, right)是没有意义的
        if (nums[middle] > target) right 更新为 middle，因为当前nums[middle]不等于target，去左区间继续寻
        找，⽽寻找区间是左闭右开区间，所以right更新为middle，即：下⼀个查询区间不会去⽐较nums[middle]
        在数组： 1,2,3,4,7,9,10中查找元素2，如图所示：（注意和⽅法⼀的区别）
*/

class Solution2
{
public:
    int search(vcetor<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size(); // 定义在target 在左闭右开的区间里, 即:[left, tight)

        while(left < right)// 因为 left == right的时候, 在[left, tight)是无效的空间, 所以 < 
        {
            int middle = left + ((right - left) >> 1);
            if(nums[middle] > target)
            {
                right = middle; // target 在左区间, [left, middle)
            }
            else if(nums[middle] < target)
            {
                left = middle + 1; // target 在右区间, [middle + 1, right)
            }
            else
            {
                // nums[middle] == target
                return middle;// 找到目标值,返回下标
            }
        }
    }
    // 未找到目标值
    return -1;
};

/*
    二分法的前提是有序
    其实主要是对区间的定义理解清楚, 在循环中始终坚持根据查找区间的定义来做边界处理
    区间的定义就是不变量
    那么在循环中, 移动 left 和 right 就是在做区间的划分
*/


