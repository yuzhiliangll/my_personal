#include "hash_table.h"
#include <iostream>
#include <string>

int main() 
{
    auto hashFunc = [](const std::string& key) -> size_t 
    {
        std::hash<std::string> hash;
        return hash(key);
    };

    auto compareFunc = [](const std::string& a, const std::string& b) -> bool 
    {
        return a == b;
    };

    HashTable<std::string, std::string> ht(10, hashFunc, compareFunc);

    ht.insert("apple", "red");
    ht.insert("banana", "yellow");
    ht.insert("grape", "purple");
    ht.insert("apple", "green");

    ht.display();

    auto searchResult = ht.search("banana");
    if (searchResult) {
        std::cout << "Found: " << searchResult->key << " -> " << searchResult->value << std::endl;
    } else {
        std::cout << "Not Found: banana" << std::endl;
    }

    ht.deleteFirst("apple");
    ht.display();

    return 0;
}





