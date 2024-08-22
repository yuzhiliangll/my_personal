#include "hash_table.h"
#include <stdlib.h> // malloc free  calloc
#include <string.h> // strcmp
#include <stdio.h>


// 计算哈希表的负载因子
static double hash_table_load_factor(const hash_table_t *ht);

// 扩容哈希表
static int hash_table_resize(hash_table_t *ht, size_t new_size);

// 缩容哈希表
static int hash_table_shrink(hash_table_t *ht, size_t new_size);

// 创建哈希表
/*
    参数解释
            size:

            类型: size_t
            描述: 哈希表的初始大小，即数组的长度。这个值决定了哈希表的容量。
            hash_func:

            类型: hash_table_hash_func
            描述: 指向哈希函数的指针。该函数用于将键映射到哈希表的数组索引位置。
            compare_func:

            类型: hash_table_compare_func
            描述: 指向比较函数的指针。该函数用于比较两个键是否相等，以处理哈希表中的冲突。
            free_func:

            类型: void (*)(void *data)
            描述: 指向释放函数的指针。该函数用于释放哈希表中元素的内存。
            display_func:

            类型: void (*)(const void *key, const void *value)
            描述: 指向显示函数的指针。该函数用于展示哈希表中的元素。
*/
hash_table_t *hash_table_create(size_t size, hash_table_hash_func hash_func, 
                                hash_table_compare_func compare_func, 
                                void (*free_func)(void *data),
                                void (*display_func)(const void *key, const void *value))
{
    hash_table_t *ht = malloc(sizeof(hash_table_t));// 分配内存 -- 用于存储哈希表结构体
    if (!ht)
    {
        perror("hash_table_create: malloc");
        return NULL;
    }

    /*
        申请一个大小为 size * sizeof(void *) 的内存块，用于存储哈希表的数组（table）。
        使用 calloc 初始化所有内存为零，确保每个表项指针初始为 NULL。
    */
    ht->table = (void **)calloc(size, sizeof(void *));// 分配内存 -- 用于存储哈希表中的元素
    if (!ht->table)
    {
        perror("hash_table_create: calloc");
        free(ht);// 释放之前分配的内存
        return NULL;
    }

    ht->size = size;// 设置哈希表的大小
    ht->count = 0;// 设置哈希表中的元素数量为 0
    ht->hash_func = hash_func;// 设置哈希函数
    ht->compare_func = compare_func;// 设置比较函数
    ht->free_func = free_func;// 设置释放函数
    ht->display_func = display_func;// 设置显示函数

    ht->load_factor = 0.0;// 设置负载因子为 0.0 --- 实际元素数量与表大小的比例
    ht->max_load_factor = 0.75;// 设置最大负载因子为 0.75
    ht->min_load_factor = 0.25;// 设置最小负载因子为 0.25

    return ht;// 返回哈希表结构体的指针
}

// 计算哈希表的负载因子
static double hash_table_load_factor(const hash_table_t *ht)
{
    return (double)ht->count / ht->size;// 计算负载因子
}

// 哈希表扩容 -- 扩容通常是在负载因子超过阈值时进行，以保持哈希表的性能。
/*
    功能:
        当负载因子超过最大负载因子时，需要扩容哈希表。
        扩容时，通常将哈希表的大小加倍，并重新计算所有元素的哈希值，将它们插入到新的哈希表中。
        扩容后，哈希表的大小将变为原来的两倍，负载因子将降低，从而提高哈希表的性能。
    参数解释
        ht:
        类型: hash_table_t *
        描述: 指向要扩容的哈希表的指针。

        new_size:
        类型: size_t
        描述: 扩容后的新大小，即哈希表的新容量。
*/
// 扩容哈希表
static int hash_table_resize(hash_table_t *ht, size_t new_size)
{
    // 保存当前哈希表的状态
    void **old_table = ht->table;
    size_t old_size = ht->size;

    // 创建新的哈希表
    ht->table = (void **)calloc(new_size, sizeof(void *));
    if(!ht->table)
    {
        return -1;// 内存分配失败
    }
    ht->size = new_size; // 更新
    ht->count = 0; // 重置元素数量

    // 将旧表中的元素重新插入到新表中
    for (size_t i = 0; i < old_size; ++i)
    {
        if (old_table[i])
        {
            void *element = old_table[i];
            while(element)
            {
                void *next = ((hash_table_search_result_t *)element)->next;
                hash_table_insert(ht, ((hash_table_search_result_t *)element)->key, ((hash_table_search_result_t *)element)->value);
                element = next;
            }
        }
    }

    // 释放旧旧哈希值
    free(old_table);

    return 0;
}

// 缩容哈希表
static int hash_table_shrink(hash_table_t *ht, size_t new_size)
{
    if (new_size >= ht->size)
    {
        return -1;
    }
    return hash_table_resize(ht, new_size);
}

// 插入元素到哈希表
/*
    键相同但值不同的情况：在链表中继续插入新节点。
    避免键相同且值相同的情况下重复插入：检查值是否已存在，避免重复插入。
*/
int hash_table_insert(hash_table_t *ht, void *key, void *value) 
{
    size_t index = ht->hash_func(key) % ht->size;
    void *current = ht->table[index];
    hash_table_search_result_t *prev = NULL;// 记录前一个节点

    // 查找是否已有相同键的元素
    while (current) 
    {
        hash_table_search_result_t *entry = (hash_table_search_result_t *)current;
        if (ht->compare_func(entry->key, key) == 0) 
        {
            // 键相同，检查值
            if (ht->compare_func(entry->value, value) == 0) 
            {
                return 0; // 值相同，不做操作
            }
            // 键相同且值不同，插入新值到链表中
            hash_table_search_result_t *new_entry = (hash_table_search_result_t *)malloc(sizeof(hash_table_search_result_t));
            if (!new_entry) 
            {
                return -1; // 内存分配失败
            }
            new_entry->key = key;
            new_entry->value = value;
            new_entry->next = entry->next;
            entry->next = new_entry;
            ++ht->count;
            // 检查负载因子是否超出最大值，若超出则扩容
            if (hash_table_load_factor(ht) > ht->max_load_factor) 
            {
                if (hash_table_resize(ht, ht->size * 2) != 0) 
                {
                    return -1; // 扩容失败
                }
            }
            return 0;
        }
        prev = entry;// prev指向当前元素
        current = entry->next;// 
    }

    // 键不同，插入新元素到链表的头部
    hash_table_search_result_t *new_entry = (hash_table_search_result_t *)malloc(sizeof(hash_table_search_result_t));
    if (!new_entry) 
    {
        return -1; // 内存分配失败
    }
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;
    ++ht->count;

    // 检查负载因子是否超出最大值，若超出则扩容
    if (hash_table_load_factor(ht) > ht->max_load_factor) 
    {
        if (hash_table_resize(ht, ht->size * 2) != 0) 
        {
            return -1; // 扩容失败
        }
    }
    return 0;
}


// 查找哈希表中的元素
hash_table_search_result_t *hash_table_search(const hash_table_t *ht, const void *key) 
{
    size_t index = ht->hash_func(key) % ht->size;
    void *current = ht->table[index];

    while (current) 
    {
        hash_table_search_result_t *entry = (hash_table_search_result_t *)current;
        if (ht->compare_func(entry->key, key) == 0) 
        {
            return entry; // 找到匹配的元素
        }
        current = entry->next;
    }
    return NULL; // 未找到
}

// 删除哈希表中的第一个匹配元素
int hash_table_delete_first(hash_table_t *ht, const void *key) 
{
    size_t index = ht->hash_func(key) % ht->size;
    void **current = &ht->table[index];
    while (*current) 
    {
        hash_table_search_result_t *entry = (hash_table_search_result_t *)(*current);
        if (ht->compare_func(entry->key, key) == 0) 
        {
            *current = entry->next;
            if (ht->free_func) 
            {
                ht->free_func(entry->key);
                ht->free_func(entry->value);
            }
            free(entry);
            --ht->count;

            // 检查负载因子是否低于最小值，若低于则缩容
            if (hash_table_load_factor(ht) < ht->min_load_factor && ht->size > 1) 
            {
                if (hash_table_shrink(ht, ht->size / 2) != 0) 
                {
                    return -1; // 缩容失败
                }
            }
            return 0;
        }
        current = &entry->next;
    }
    return -1; // 未找到要删除的元素
}

// 删除哈希表中的所有匹配元素
int hash_table_delete_all(hash_table_t *ht, const void *key) 
{
    size_t index = ht->hash_func(key) % ht->size;
    void **current = &ht->table[index];
    int result = -1;

    while (*current) 
    {
        hash_table_search_result_t *entry = (hash_table_search_result_t *)(*current);
        if (ht->compare_func(entry->key, key) == 0) 
        {
            *current = entry->next;
            if (ht->free_func) 
            {
                ht->free_func(entry->key);
                ht->free_func(entry->value);
            }
            free(entry);
            --ht->count;
            result = 0;
        } else {
            current = &entry->next;
        }
    }

    // 检查负载因子是否低于最小值，若低于则缩容
    if (result == 0 && hash_table_load_factor(ht) < ht->min_load_factor && ht->size > 1) 
    {
        if (hash_table_shrink(ht, ht->size / 2) != 0) 
        {
            return -1; // 缩容失败
        }
    }
    return result;
}

// 显示哈希表中的所有元素
void hash_table_display(const hash_table_t *ht) 
{
    for (size_t i = 0; i < ht->size; ++i) 
    {
        void *current = ht->table[i];
        while (current) 
        {
            hash_table_search_result_t *entry = (hash_table_search_result_t *)current;
            if (ht->display_func) 
            {
                ht->display_func(entry->key, entry->value);
            }
            current = entry->next;
        }
    }
}

// 销毁哈希表
void hash_table_destroy(hash_table_t *ht) 
{
    for (size_t i = 0; i < ht->size; ++i) 
    {
        void *current = ht->table[i];
        while (current) 
        {
            hash_table_search_result_t *entry = (hash_table_search_result_t *)current;
            current = entry->next;
            if (ht->free_func) 
            {
                ht->free_func(entry->key);
                ht->free_func(entry->value);
            }
            free(entry);
        }
    }
    free(ht->table);
    free(ht);
}

