#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>// size_t

// 哈希表元素的比较函数
/*
    用途: 比较两个哈希表元素的函数指针类型。
    参数: const void *a 和 const void *b 指向两个要比较的元素，类型为 void *，表示可以指向任何类型的数据，但不允许修改数据。
    返回值: int 类型的值，用于比较结果。
            通常，返回值为负、零或正，分别表示第一个元素小于、等于或大于第二个元素。
*/
typedef int (*hash_table_compare_func)(const void *a, const void *b);

// 哈希表元素的哈希函数类型
/*
    用途: 计算哈希值的函数指针类型。
    参数: const void *key 指向哈希表元素的键，类型为 void *，表示可以指向任何类型的数据，但不允许修改数据。
    返回值: size_t 类型的哈希值，用于确定键在哈希表中的位置。
*/
typedef size_t (*hash_table_hash_func)(const void *key);// const void * 表示指向常量数据的指针，可以指向任何类型的数据，但不能通过这个指针修改数据

// 用于存储查找结果的链表节点
typedef struct hash_table_search_result 
{
    void *key;                            // 查找结果的键
    void *value;                          // 查找结果对应的值           
    struct hash_table_search_result *next;// 指向下一个节点的指针
} hash_table_search_result_t;

// 哈希表结构体 和相关的函数指针类型
typedef struct hash_table 
{
    // 存储哈希表中的所有元素。每个元素是一个指向数据的指针（void *），具体的数据类型由实际使用时决定。
    void **table;                      // 哈希表数组
    size_t size;                      // 哈希表的大小
    size_t count;                     // 当前元素数量

    // 用于计算哈希值的函数的指针。该函数根据键计算哈希值，用于决定元素在哈希表中的位置。
    hash_table_hash_func hash_func;   // 哈希函数

    // 指向用于比较两个元素的函数的指针。该函数用于判断两个元素是否相等，通常用于处理哈希冲突。
    hash_table_compare_func compare_func; // 比较函数

    // 用于释放哈希表中元素内存的函数的指针。当元素从哈希表中删除时，或者在销毁哈希表时，这个函数用于释放与元素相关的内存。
    void (*free_func)(void *data);    // 释放函数

    // 用于显示哈希表中元素内容的函数的指针。该函数用于显示元素的内容，通常用于调试或输出。
    void (*display_func)(const void *key, const void *value); // 显示函数

    double load_factor;     // 哈希表的负载因子，用于判断是否需要扩容
    double max_load_factor; //  触发扩容的负载因子阈值
    double min_load_factor; // 触发缩容的负载因子阈值
} hash_table_t;

// 创建哈希表
hash_table_t *hash_table_create(size_t size, hash_table_hash_func hash_func, 
                                hash_table_compare_func compare_func, 
                                void (*free_func)(void *data),
                                void (*display_func)(const void *key, const void *value));

/*
    函数指针类型: 用于定义哈希表的各种操作，如计算哈希值、比较元素、释放内存和显示元素
    哈希表结构体: 定义了哈希表的主要属性和功能，包括存储数组、大小、元素计数、哈希函数、比较函数、释放函数和显示函数。
    创建函数: 用于初始化和创建一个新的哈希表，设置所需的函数和参数，以便哈希表可以根据特定需求进行操作。
*/

/******************************************************************************************** */

// 插入元素到哈希表
int hash_table_insert(hash_table_t *ht, void *key, void *value);

// 查找哈希表中的元素
hash_table_search_result_t *hash_table_search(const hash_table_t *ht, const void *key);

// 删除哈希表中的第一个匹配元素
int hash_table_delete_first(hash_table_t *ht, const void *key);

// 删除哈希表中的所有匹配元素
int hash_table_delete_all(hash_table_t *ht, const void *key);

// 显示哈希表中的所有元素
void hash_table_display(const hash_table_t *ht);

// 销毁哈希表
void hash_table_destroy(hash_table_t *ht);

#endif // HASH_TABLE_H