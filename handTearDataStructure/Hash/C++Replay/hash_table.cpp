// #include "hash_table.h"
// #include <iostream>


// template <typename Key, typename Value>
// HashTable<Key, Value>::HashTable(size_t size, HashFunc hashFunc, CompareFunc compareFunc)
//     : size(size), count(0), hashFunc(hashFunc), compareFunc(compareFunc),
//       maxLoadFactor(0.75), minLoadFactor(0.25) {
//     table.resize(size);
// }

// template <typename Key, typename Value>
// double HashTable<Key, Value>::loadFactor() const {
//     return static_cast<double>(count) / size;
// }

// template <typename Key, typename Value>
// bool HashTable<Key, Value>::resize(size_t newSize) {
//     std::vector<std::shared_ptr<HashNode<Key, Value>>> oldTable = std::move(table);
//     size = newSize;
//     table.resize(newSize);
//     count = 0;

//     for (auto& node : oldTable) {
//         while (node) {
//             insert(node->key, node->value);
//             node = node->next;
//         }
//     }
//     return true;
// }

// template <typename Key, typename Value>
// bool HashTable<Key, Value>::shrink(size_t newSize) {
//     if (newSize >= size) return false;
//     return resize(newSize);
// }

// template <typename Key, typename Value>
// bool HashTable<Key, Value>::insert(const Key& key, const Value& value) {
//     size_t index = hashFunc(key) % size;
//     auto current = table[index];

//     while (current) {
//         if (compareFunc(current->key, key)) {
//             if (current->value == value) {
//                 return false; // 如果键值对已存在，不执行插入操作
//             }
//             auto newNode = std::make_shared<HashNode<Key, Value>>(key, value);
//             newNode->next = current->next;
//             current->next = newNode;
//             ++count;
//             if (loadFactor() > maxLoadFactor) {
//                 resize(size * 2);
//             }
//             return true;
//         }
//         current = current->next;
//     }

//     auto newNode = std::make_shared<HashNode<Key, Value>>(key, value);
//     newNode->next = table[index];
//     table[index] = newNode;
//     ++count;
//     if (loadFactor() > maxLoadFactor) {
//         resize(size * 2);
//     }
//     return true;
// }

// template <typename Key, typename Value>
// std::shared_ptr<HashNode<Key, Value>> HashTable<Key, Value>::search(const Key& key) const {
//     size_t index = hashFunc(key) % size;
//     auto current = table[index];

//     while (current) {
//         if (compareFunc(current->key, key)) {
//             return current;
//         }
//         current = current->next;
//     }
//     return nullptr;
// }

// template <typename Key, typename Value>
// bool HashTable<Key, Value>::deleteFirst(const Key& key) {
//     size_t index = hashFunc(key) % size;
//     auto current = table[index];
//     std::shared_ptr<HashNode<Key, Value>> prev = nullptr;

//     while (current) {
//         if (compareFunc(current->key, key)) {
//             if (prev) {
//                 prev->next = current->next;
//             } else {
//                 table[index] = current->next;
//             }
//             --count;
//             if (loadFactor() < minLoadFactor && size > 1) {
//                 shrink(size / 2);
//             }
//             return true;
//         }
//         prev = current;
//         current = current->next;
//     }
//     return false;
// }

// template <typename Key, typename Value>
// bool HashTable<Key, Value>::deleteAll(const Key& key) {
//     size_t index = hashFunc(key) % size;
//     auto current = table[index];
//     bool deleted = false;

//     while (current) {
//         if (compareFunc(current->key, key)) {
//             current = current->next;
//             --count;
//             deleted = true;
//         } else {
//             break;
//         }
//     }
//     table[index] = current;

//     if (deleted && loadFactor() < minLoadFactor && size > 1) {
//         shrink(size / 2);
//     }
//     return deleted;
// }

// template <typename Key, typename Value>
// void HashTable<Key, Value>::display() const {
//     for (const auto& node : table) {
//         auto current = node;
//         while (current) {
//             std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
//             current = current->next;
//         }
//     }
// }



