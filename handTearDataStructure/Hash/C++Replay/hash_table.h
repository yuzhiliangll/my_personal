#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <functional> // std::hash
#include <memory>// std::shared_ptr
#include <vector>// std::vector


template <typename Key, typename Value>
struct HashNode
{
    Key key;// 键
    Value value;// 值

    std::shared_ptr<HashNode<Key, Value>> next;// 下一个节点

    HashNode(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {} // 节点构造函数(默认public)
};

template <typename Key, typename Value>
class HashTable
{
public:
    using HashFunc = std::function<size_t(const Key&)>;// 哈希函数
    using CompareFunc = std::function<bool(const Key&, const Key&)>;// 比较函数

    HashTable(size_t size, HashFunc hashFunc, CompareFunc compareFunc);// 构造函数
    bool insert(const Key& key, const Value& value);// 插入键值对
    std::shared_ptr<HashNode<Key, Value>> search(const Key& key) const;// 查找键
    bool deleteFirst(const Key& key);// 删除键
    bool deleteAll(const Key& key);
    void display() const;// 打印哈希表
    void destroy();  // 这里的destroy实际不需要实现，因为智能指针会自动管理内存


private:
    double loadFactor() const; // 负载因子
    bool resize(size_t newSize);// 扩容
    bool shrink(size_t newSize);// 缩容

    std::vector<std::shared_ptr<HashNode<Key, Value>>> table;// 哈希表
    size_t size;// 容量
    size_t count;// 元素个数
    HashFunc hashFunc;// 哈希函数
    CompareFunc compareFunc;// 比较函数
    double maxLoadFactor; // 最大负载因子
    double minLoadFactor; // 最小负载因子

};


#include <iostream>
/*
    总结
    将模板类的实现放在同一个文件里通常是指将模板类的实现和声明都放在同一个头文件中，
    或者在.cpp文件中包含头文件。
*/

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size, HashFunc hashFunc, CompareFunc compareFunc)
    : size(size), count(0), hashFunc(hashFunc), compareFunc(compareFunc),
      maxLoadFactor(0.75), minLoadFactor(0.25) {
    table.resize(size);
}

template <typename Key, typename Value>
double HashTable<Key, Value>::loadFactor() const {
    return static_cast<double>(count) / size;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::resize(size_t newSize) {
    std::vector<std::shared_ptr<HashNode<Key, Value>>> oldTable = std::move(table);
    size = newSize;
    table.resize(newSize);
    count = 0;

    for (auto& node : oldTable) {
        while (node) {
            insert(node->key, node->value);
            node = node->next;
        }
    }
    return true;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::shrink(size_t newSize) {
    if (newSize >= size) return false;
    return resize(newSize);
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {
    size_t index = hashFunc(key) % size;
    auto current = table[index];

    while (current) {
        if (compareFunc(current->key, key)) {
            if (current->value == value) {
                return false; // 如果键值对已存在，不执行插入操作
            }
            auto newNode = std::make_shared<HashNode<Key, Value>>(key, value);
            newNode->next = current->next;
            current->next = newNode;
            ++count;
            if (loadFactor() > maxLoadFactor) {
                resize(size * 2);
            }
            return true;
        }
        current = current->next;
    }

    auto newNode = std::make_shared<HashNode<Key, Value>>(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    ++count;
    if (loadFactor() > maxLoadFactor) {
        resize(size * 2);
    }
    return true;
}

template <typename Key, typename Value>
std::shared_ptr<HashNode<Key, Value>> HashTable<Key, Value>::search(const Key& key) const {
    size_t index = hashFunc(key) % size;
    auto current = table[index];

    while (current) {
        if (compareFunc(current->key, key)) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::deleteFirst(const Key& key) {
    size_t index = hashFunc(key) % size;
    auto current = table[index];
    std::shared_ptr<HashNode<Key, Value>> prev = nullptr;

    while (current) {
        if (compareFunc(current->key, key)) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            --count;
            if (loadFactor() < minLoadFactor && size > 1) {
                shrink(size / 2);
            }
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::deleteAll(const Key& key) {
    size_t index = hashFunc(key) % size;
    auto current = table[index];
    bool deleted = false;

    while (current) {
        if (compareFunc(current->key, key)) {
            current = current->next;
            --count;
            deleted = true;
        } else {
            break;
        }
    }
    table[index] = current;

    if (deleted && loadFactor() < minLoadFactor && size > 1) {
        shrink(size / 2);
    }
    return deleted;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::display() const {
    for (const auto& node : table) {
        auto current = node;
        while (current) {
            std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
            current = current->next;
        }
    }
}




#endif // __HASH_TABLE_H__