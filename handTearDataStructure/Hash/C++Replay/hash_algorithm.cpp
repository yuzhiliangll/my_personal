/*
    两个字符串是字母异位词（Anagram）
    如果它们包含的字符相同，并且每个字符的出现次数也相同，但字符的顺序可以不同。
    例如，"listen" 和 "silent" 是字母异位词。


    问题描述
    给定一个字符串数组，找出其中的字母异位词，并将它们分组。

    输入：["eat", "tea", "tan", "ate", "nat", "bat"]
    输出：[["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]

    思路
    利用哈希表，我们可以将字母异位词分组。具体做法是将每个字符串进行处理，
    使得异位词有相同的标识符，然后将它们存储在哈希表中，最后输出哈希表的值。

    步骤
    1. 创建哈希表：使用一个哈希表，键为异位词的标识符，值为字符串列表。
    2. 计算标识符：对于每个字符串，计算出一个唯一的标识符（例如，将字符串中的字符排序后得到的字符串），这个标识符相同的字符串都是字母异位词。
    3. 分组：将每个字符串根据其标识符放入哈希表中。
    4. 返回结果：哈希表中每个键对应的值就是字母异位词的一个分组。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    unordered_map<string, vector<string>> hashTable;// 哈希表，键为异位词的标识符，值为字符串列表

    // 遍历字符串数组
    for (string& s : strs)
    {
        // 对字符串中的字符进行排序
        string key = s;
        sort(key.begin(), key.end());

        // 将排序后的字符串作为键, 将原字符串添加到哈希表中
        hashTable[key].push_back(s);
    }

    // 将哈希表中的值（即分组后的字符串列表）存入结果向量
    vector<vector<string>> result;
    for (auto& entry : hashTable)  
    {
        result.push_back(entry.second);// entry.second是字符串列表
    }
    /*
        第二种遍历
        for (unordered_map<string, vector<string>>::iterator it = hashTable.begin(); it != hashTable.end(); ++it)
        {
            result.push_back(it->second);// it->second是 vector<string>---也是字符串列表
        }
    */

    return result;
}

int main()
{
    vector<string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
    vector<vector<string>> result = groupAnagrams(strs);

    // 输出结果
    for (auto& group : result) 
    {
        cout << "[";
        for (auto& word : group) 
        {
            cout << word << " ";
        }
        cout << "]\n";
    }

    return 0;
}



