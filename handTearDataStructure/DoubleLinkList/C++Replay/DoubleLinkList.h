#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__

#include <iostream>
#include <functional>// for std::function


typedef void* ElementType; // ElementType is a pointer to void

class Node// Node is a class
{
public:
    ElementType value; // value is a pointer to void
    Node* next; // next is a pointer to Node
    Node* prev; // prev is a pointer to Node

    Node(ElementType val) : value(val), next(nullptr), prev(nullptr) {} // constructor

};

class DoubleLinkList
{
private:
    Node* head; // head is a pointer to Node
    Node* tail; // tail is a pointer to Node
    int len;

    Node* CreateNode(ElementType element);// create a new node

public:
    DoubleLinkList(); // Constructor
    ~DoubleLinkList(); // Destructor

    void Init(); // Initialize the list
    void InsertTail(ElementType element); // Insert at the end
    void InsertHead(ElementType element); // Insert at the beginning
    void InsertByIndex(int index, ElementType element); // Insert at index
    Node* FindByIndex(int index) const; // Find node by index
    void UpdateNodeByIndex(int index, ElementType newValue); // Update node value by index
    void Travel(std::function<void(ElementType)> func) const; // Traverse from head
    void ReTravel(std::function<void(ElementType)> func) const; // Traverse from tail
    void RemoveByIndex(int index); // Remove node by index
    void RemoveByElement(ElementType element, std::function<bool(ElementType, ElementType)> func); // Remove node by value
    void Free(std::function<void(ElementType)> func); // Free all nodes
    void Clear(); // Clear all nodes
    DoubleLinkList FindByElement(ElementType element, std::function<bool(ElementType, ElementType)> func) const; // Find nodes by value
    DoubleLinkList Merge(const DoubleLinkList& other) const; // Merge with another list
    void Reverse(); // Reverse the list
    bool IsEmpty() const; // Check if the list is empty
    int GetLength() const; // Get the length of the list
    Node* GetHead() const; // Get the head node
    Node* GetTail() const; // Get the tail node

};

#endif // __DOUBLELINKLIST_H__