#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 假设这些定义在你的头文件中
#include "hash_table.h"

// 自定义哈希函数
size_t hash_function(const void *key) 
{
    const char *str = (const char *)key;// 将 key 转换为字符串
    size_t hash = 5381;// 初始化哈希值为 5381，这是 DJB2 算法的标准初始值
    int c;

    while ((c = *str++)) // 逐字符读取字符串，直到遇到 null 终止符 '\0
    {
        /*
            hash = ((hash << 5) + hash) + c: 哈希计算的核心部分。这个公式可以拆解为：
            hash << 5: 将哈希值左移 5 位，相当于乘以 32。
            ((hash << 5) + hash): 计算 hash * 33，其中 33 是常数。
            ((hash << 5) + hash) + c: 将当前字符的 ASCII 值 c 加入到哈希值中。
            这个公式实际上是 hash * 33 + c，它在 DJB2 算法中用于处理哈希碰撞。
        */
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// 自定义比较函数
int compare_function(const void *a, const void *b) 
{
    return strcmp((const char *)a, (const char *)b);// 比较两个字符串
}

// 自定义释放函数
void free_function(void *ptr) 
{
    free(ptr);
}

// 自定义显示函数
void display_function(const void *key, const void *value) 
{
    printf("Key: %s, Value: %s\n", (const char *)key, (const char *)value);// 打印键和值
}

int main() 
{
    // 创建哈希表
    hash_table_t *ht = hash_table_create(10, hash_function, compare_function, free_function, display_function);
    if (!ht) 
    {
        printf("Failed to create hash table.\n");
        return 1;
    }

    // 测试数据
    char *keys[] = {"apple", "banana", "orange", "grape", "apple"};
    char *values[] = {"fruit1", "fruit2", "fruit3", "fruit4", "fruit5"};

    // 插入数据
    for (size_t i = 0; i < 5; ++i) 
    {
        char *key = strdup(keys[i]);// 复制键
        char *value = strdup(values[i]);// 复制值
        if (hash_table_insert(ht, key, value) != 0) // 插入键值对
        {
            printf("Failed to insert key: %s\n", key);
            free(key); 
            free(value);
        }
    }

    // 显示哈希表内容
    printf("Hash table contents:\n");
    hash_table_display(ht);

    // 查找数据
    for (size_t i = 0; i < 5; ++i) 
    {
        hash_table_search_result_t *result = hash_table_search(ht, keys[i]);
        if (result) 
        {
            printf("Found key: %s, Value: %s\n", (const char *)result->key, (const char *)result->value);
        } 
        else 
        {
            printf("Key %s not found.\n", keys[i]);
        }
    }

    // 删除数据
    for (size_t i = 0; i < 2; ++i) 
    { // 删除前两个键
        if (hash_table_delete_first(ht, keys[i]) == 0) 
        {
            printf("Deleted key: %s\n", keys[i]);
        } 
        else 
        {
            printf("Failed to delete key: %s\n", keys[i]);
        }
    }

    // 显示哈希表内容
    printf("Hash table contents after deletion:\n");
    hash_table_display(ht);

    // 销毁哈希表
    hash_table_destroy(ht);

    return 0;
}
