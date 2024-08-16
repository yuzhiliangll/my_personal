/*
    给你⼀个数组 nums 和⼀个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新⻓度。
    不要使⽤额外的数组空间，你必须仅使⽤ O(1) 额外空间并原地修改输⼊数组。

    元素的顺序可以改变。你不需要考虑数组中超出新⻓度后⾯的元素。
    示例 1:
    给定 nums = [3,2,2,3], val = 3,
    函数应该返回新的⻓度 2, 并且 nums 中的前两个元素均为 2。
    你不需要考虑数组中超出新⻓度后⾯的元素。

    示例 2:
    给定 nums = [0,1,2,2,3,0,4,2], val = 2,
    函数应该返回新的⻓度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
*/

/*
    暴力解法
    两层for循环
    一个for循环遍历数组
    第二个for循环更新数组
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        int size = nums.size();
        for (int i = 0; i < size; i++)
        {
            if (nums[i] == val)// 发现需要移除的元素, 就将数组集体向前移
            {
                for(int j = i + 1; j < size; j++)
                {
                    nums[j - 1] = nums[j]; 
                }
                i--; // 因为下标i以后的数值都向前移动了一位，所以i也向前移动一位
                /*
                    i-- 的作用是确保遍历数组时不会跳过任何元素。
                    数组元素前移：当你找到一个需要移除的元素（即 nums[i] == val 时），
                    你会将从 i 之后的所有元素向前移动一位，这样就覆盖掉了当前的元素。

                    问题：可能跳过的元素：假设你有一个元素序列 [1, 2, 3, 4, 2, 5]，你正在移除值为 2 的元素。
                    当你移除第一个 2 时，数组变为 [1, 3, 4, 2, 5]。
                    此时 i 增加到下一个位置 i+1，如果不使用 i--，则会直接检查原来的 3 位置（现在是 4），而跳过了刚移动到 i 位置的 2。

                    i-- 的作用：在移除一个元素并将其后的元素前移后，你需要将 i 减去1 (i--)。
                    这是因为你希望重新检查当前 i 位置的元素，因为它是从后面移动过来的。

                */
                size--; // 此时数组的大小减小1
            }
        }
        return size;
    }

};

int main() 
{
    std::vector<int> nums = {3, 2, 2, 3, 4, 2, 5};
    int val = 2;

    Solution solution;

    int newSize = solution.removeElement(nums, val);

    std::cout << "New size after removing " << val << ": " << newSize << std::endl;
    std::cout << "Modified array: ";
    for (int i = 0; i < newSize; i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}


/*
    双指针法
    双指针(快慢指针法): 通过一个快指针和慢指针在一个for循环下完成两个for循环的工作

    定义快慢指针

        快指针: 寻找新数组的元素,新数组就是不含目标元素的数组
        慢指针: 指向更新 新数组下标的位置
*/

class Solution2
{
public:
    int removeElement(std::vector<int>& nums, int val) 
    {
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < nums.size(); fastIndex++)
        {
            if(val != nums[fastIndex])
            {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex; // 新数组下标
    }

};



