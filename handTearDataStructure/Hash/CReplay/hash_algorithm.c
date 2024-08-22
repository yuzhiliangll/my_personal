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
    1. 定义哈希表结构：每个哈希表的桶存储一个链表，链表的节点包含排序后的字符串（作为键）和一个字符串列表。
    2. 计算标识符：对字符串中的字符进行排序，生成唯一的键。
    3. 分组：将原字符串插入到哈希表中，如果找到相同键的桶，就将字符串加入对应的链表中。
    4. 输出结果：遍历哈希表，输出所有分组。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

// 链表节点结构
typedef struct Node
{
    char* key;// 排序后的字符串
    char** anagrams;// 字符串列表
    int count;// 字符串列表的长度
    struct Node* next;// 下一个节点

}Node;

// 哈希表结构
typedef struct HashTable
{
    Node* table[HASH_SIZE];
}HashTable;

// 哈希函数--用于将字符串映射到一个特定范围内的整数值，这个整数值就是哈希值
/*
    遍历字符串 "abc"，依次处理每个字符。

    第一步：处理字符 'a'

    字符 'a' 的 ASCII 值为 97。
    计算：hash = 0 * 31 + 97 = 97
    第二步：处理字符 'b'

    字符 'b' 的 ASCII 值为 98。
    计算：hash = 97 * 31 + 98 = 3105
    第三步：处理字符 'c'

    字符 'c' 的 ASCII 值为 99。
    计算：hash = 3105 * 31 + 99 = 96354
    遍历完字符串后，得到的哈希值是 96354。

    最后，对哈希值取模运算，使其在 0 到 HASH_SIZE-1 之间：
    hash = 96354 % 100 = 54

*/
unsigned int hash(char* str)
{
    unsigned int hash = 0;// 哈希值
    while (*str)// 遍历字符串
    {
        hash = hash * 31 + *str++;// 哈希算法
    }
    return hash % HASH_SIZE;// 取模运算
}

// 创建新的节点
Node* createNode(char* key, char* word)// 键值对
{
    Node* node = (Node*)malloc(sizeof(Node));// 分配内存
    node->key = strdup(key);// 复制字符串
    node->anagrams = (char**)malloc(sizeof(char*));// 分配内存
    node->anagrams[0] = strdup(word);// 复制字符串
    node->count = 1;// 字符串列表的长度
    node->next = NULL;// 下一个节点
    return node;// 返回节点
}

// 插入节点到哈希表中
void insert(HashTable* hashTable, char* key, char* word)
{
    unsigned int index = hash(key);// 
    Node* node = hashTable->table[index];// 获取节点

    // 遍历链表 查看是否有相同的键
    while(node)
    {
        if (strcmp(node->key, key) == 0) 
        {
            // 如果找到了相同的键，将单词添加到字符串列表中
            node->anagrams = (char**)realloc(node->anagrams, (node->count + 1) * sizeof(char*));
            node->anagrams[node->count] = strdup(word);
            node->count++;
            return;
        }
        node = node->next;// 遍历链表
    }

    // 如果没有找到, 创建新节点并插入链表头部
    Node* newNode = createNode(key, word);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;

}

// 对字符串中的字符进行排序
void sortString(char* str)
{
    int len = strlen(str);// 获取字符串长度
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if(str[i] > str[j])
            {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

// 打印哈希表中的字母异位词分组
void printAnagrams(HashTable* hashTable)
{
    for (int i = 0; i < HASH_SIZE; i++)// 遍历哈希表
    {
        Node* node = hashTable->table[i];
        while(node)// 遍历链表
        {
            printf("[");// 打印字母异位词分组
            for (int j = 0; j < node->count; j++)
            {
                printf("%s ", node->anagrams[j]);// 
            }
            printf("]\n");
            node = node->next;
        }
    }
}

// 释放哈希表的内存
/*
    为什么要这样释放
    逐节点释放：哈希表的每个槽位可能存储一个链表，每个链表节点都需要逐个释放。通过 while 循环，确保链表中的每一个节点都被遍历并释放。

    释放动态分配的键：free(temp->key) 是为了释放为每个节点中的键动态分配的内存。

    释放anagrams数组中的每个字符串：anagrams 是一个字符串数组。数组中的每个字符串可能是动态分配的，因此需要逐个释放。

    释放anagrams数组：在释放完 anagrams 数组中的每个字符串后，数组本身的内存也需要释放。

    释放节点：最后，释放节点本身，避免内存泄漏。
*/
void freeHashTable(HashTable* hashTable)
{
    for (int i = 0; i < HASH_SIZE; i++)// 遍历哈希表的每一个槽位
    {
        Node* node = hashTable->table[i];// 获取当前槽位的链表头节点
        while(node)// 遍历链表
        {
            Node* temp = node;// 临时存储当前节点
            node = node->next;// 移动到下一个节点
            free(temp->key);// 释放节点中的键（假设键是动态分配的）
            for (int j = 0; j < temp->count; j++)// 释放anagrams数组中的每个字符串
            {
                free(temp->anagrams[j]);// 释放动态分配的字符串
            }
            free(temp->anagrams);// 释放anagrams数组本身
            free(temp);// 释放节点本身
        }
    }
}
/*
    假设我们有一个哈希表，其中包含以下数据：

        槽位 0:
        键 "aet" -> 字符串列表：["eat", "tea"]
        键 "ant" -> 字符串列表：["tan", "nat"]
        槽位 1:
        键 "aep" -> 字符串列表：["pea", "ape"]
    
        HashTable (哈希表)
        +----------------------+
        | table[0]             | -> Node1 -> Node2 -> NULL
        +----------------------+
        | table[1]             | -> Node3 -> NULL
        +----------------------+
        | table[2]             | -> NULL
        +----------------------+
        | ...                  |
        +----------------------+

        Node1 (槽位 0)
        +----------------------+
        | key: "aet"           |
        | anagrams: ["eat", "tea"]  |
        | next: -> Node2       |
        +----------------------+

        Node2 (槽位 0)
        +----------------------+
        | key: "ant"           |
        | anagrams: ["tan", "nat"]  |
        | next: NULL           |
        +----------------------+

        Node3 (槽位 1)
        +----------------------+
        | key: "aep"           |
        | anagrams: ["pea", "ape"]  |
        | next: NULL           |
        +----------------------+

        释放逻辑示意

        槽位 0:

        Node1:
        释放 key: "aet"
        释放 anagrams: ["eat", "tea"]
        释放 Node1 本身
        Node2:
        释放 key: "ant"
        释放 anagrams: ["tan", "nat"]
        释放 Node2 本身

        槽位 1:

        Node3:
        释放 key: "aep"
        释放 anagrams: ["pea", "ape"]
        释放 Node3 本身

        其他槽位: 没有元素，直接跳过。

        释放顺序
        从每个槽位的链表头开始，依次释放链表中的节点。
        先释放 key（假设是动态分配的）。
        释放 anagrams 数组中的每个字符串。
        释放 anagrams 数组本身。
        释放链表节点本身。
*/


int main()
{
    // 初始化哈希表
    HashTable hashTable = {0};

    // 输入字符串数组
    char* strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int size = sizeof(strs) / sizeof(strs[0]);

    // 将字符串插入哈希表
    for (int i = 0; i < size; i++) 
    {
        char sorted[100];// 用于存储排序后的字符串
        strcpy(sorted, strs[i]);// 将原字符串复制到 sorted 中
        sortString(sorted);// 对 sorted 进行排序
        insert(&hashTable, sorted, strs[i]);// 将排序后的字符串和原字符串插入哈希表
    }

    // 打印字母异位词分组
    printAnagrams(&hashTable);

    // 释放内存
    freeHashTable(&hashTable);

    return 0;
}

