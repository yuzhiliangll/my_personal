哈希表（Hash Table）是一种数据结构，用于实现快速的数据存取和查找。
它通过将键映射到一个固定大小的数组中，来支持常数时间复杂度的插入、删除和查找操作。
下面是哈希表的定义、实现原理以及实现时需要注意的一些事项。

哈希表的定义
哈希表的基本结构包括：

数组（哈希表数组）: 存储实际的数据元素。
哈希函数: 用于将键映射到数组索引的函数。
处理冲突的方法: 用于处理两个键通过哈希函数映射到同一数组位置的情况。
实现原理

1. 哈希函数
作用: 将键映射到数组的索引。

特性:
均匀性: 哈希函数应尽量均匀地分布键值，减少冲突。
效率: 应高效地计算哈希值，避免影响操作的时间复杂度。
稳定性: 相同的键应始终映射到相同的索引。

2. 处理冲突的方法
冲突是指两个不同的键通过哈希函数映射到相同的数组索引。常见的冲突处理方法有：

链表法（Separate Chaining）:

在每个数组位置上使用链表存储所有哈希到相同位置的元素。
优点: 实现简单，适用于动态变化的元素数量。
缺点: 链表可能变长，导致操作时间复杂度退化为线性时间。

开放地址法（Open Addressing）:

当发生冲突时，寻找表中下一个空闲的位置来存储元素。
常见策略:
线性探测: 逐个位置查找空闲位置。
二次探测: 使用二次函数查找空闲位置。
双重哈希: 使用第二个哈希函数决定步长。
优点: 不需要额外的链表存储。
缺点: 可能需要复杂的探测逻辑，并且性能受表的负载因子影响较大。

3. 动态调整

负载因子（Load Factor）: 存储的元素数量与数组大小的比例。负载因子过高会导致冲突增加，影响性能。


扩容:
当哈希表的负载因子（即存储的元素数量与数组大小的比例）达到一定阈值时，可以扩容。

扩容时，通常会重新计算哈希值，并将元素重新分布到新的更大的数组中。

缩容:
当元素数量减少到一定程度时，可以缩小哈希表的大小，以节省内存。

实现注意事项
选择合适的哈希函数:

应确保哈希函数能均匀地分布键，减少冲突。
哈希函数应对所有可能的输入表现良好，避免产生过多冲突。
冲突处理:

选择适当的冲突处理策略，根据实际需求和负载因子进行优化。
对于链表法，链表的性能与链表的长度相关；对于开放地址法，探测过程的复杂性与负载因子相关。
动态调整:

确定适当的负载因子阈值，以决定何时进行扩容或缩容。
扩容或缩容时，重新计算哈希值并重新分配元素，确保哈希表的性能保持在最佳状态。
内存管理:

在删除元素时，正确释放内存，避免内存泄漏。
对于开放地址法，处理删除操作时需要特别注意，确保不会影响后续的查找操作。
线程安全:

如果哈希表在多线程环境中使用，需要考虑线程安全的问题，可能需要使用锁或其他同步机制。
示例代码（链表法）
以下是一个简单的哈希表实现示例（链表法）：
```C++
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *table[TABLE_SIZE];
} HashTable;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

HashTable *create_table() {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

void insert(HashTable *hashTable, const char *key, const char *value) {
    unsigned int index = hash(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

char *search(HashTable *hashTable, const char *key) {
    unsigned int index = hash(key);
    Node *list = hashTable->table[index];
    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            return list->value;
        }
        list = list->next;
    }
    return NULL;
}

void free_table(HashTable *hashTable) 
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *list = hashTable->table[i];
        while (list != NULL) {
            Node *temp = list;
            list = list->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hashTable);
}

int main() 
{
    HashTable *hashTable = create_table();
    insert(hashTable, "name", "Alice");
    insert(hashTable, "age", "30");
    printf("Name: %s\n", search(hashTable, "name"));
    printf("Age: %s\n", search(hashTable, "age"));
    free_table(hashTable);
    return 0;
}



valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./


