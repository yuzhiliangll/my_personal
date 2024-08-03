#include <stdio.h>
#include <string>
#include <stdbool.h>

bool repeatedSubstringPattern(char* s) 
{
    if (s == NULL)
    {
        return false;
    }

    /* 记录字符串的长度 */
    int length = strlen(s);
    if (length <= 1)
    {
        return false;
    }

    for(int window = 1; window <= length / 2; window++)//从 1 到 length / 2，遍历所有可能的子串长度 window。我们只需要检查到 length / 2，因为更长的子串长度无法重复多次形成原字符串
    {
        /* 窗口的长度是否是字符串长度的因子 */
        //如果 window 不是字符串长度的因子（即 length % window != 0），则跳过当前窗口长度，继续下一次循环。
        /*
            原因：只有当 window 是字符串长度的因子时，子串才能完全重复覆盖整个字符串。
            例如，字符串长度为 8，子串长度为 3 时，8 % 3 != 0，所以长度为 3 的子串无法完全覆盖字符串。
        */
        if(length % window != 0)
        {
            continue;
        }

        /* 提取子串 */
        char subString[window + 1];//多一个字符是为了存储字符串结束符 \0
        memset(subString, 0, sizeof(subString));
        strncpy(subString, s, window);

        // 检查子串重复情况
        int repeated = true;//初始化重复标志 目的：用于记录当前窗口长度下，子串是否能重复覆盖整个字符串。
        for(int idx = window; idx <= length - window; idx += window)
        {
            //逐步检查每个长度为 window 的子串是否与第一个子串相同。
            if(strncmp(subString, s + idx, window) != 0)
            {
                repeated = false;
                break;
            }
        }

        if(repeated == true)
        {
            return true;
        }
    }
    return false;
}
/*
    
*/
