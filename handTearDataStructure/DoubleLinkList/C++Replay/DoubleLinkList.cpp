#include "DoubleLinkList.h"
#include <stdexcept>

// Constructor
DoubleLinkList::DoubleLinkList() : head(nullptr), tail(nullptr), len(0) {}

// Destructor
DoubleLinkList::~DoubleLinkList() {
    Clear();
}

// Initialize the list
void DoubleLinkList::Init() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Create a new node
Node* DoubleLinkList::CreateNode(ElementType element) {
    return new Node(element);
}

// Insert at the end
void DoubleLinkList::InsertTail(ElementType element) {
    Node* newNode = CreateNode(element);
    if (tail == nullptr) { // If the list is empty
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    len++;
}

// Insert at the beginning
void DoubleLinkList::InsertHead(ElementType element) {
    Node* newNode = CreateNode(element);
    if (head == nullptr) { // If the list is empty
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    len++;
}

// Insert at index
void DoubleLinkList::InsertByIndex(int index, ElementType element) {
    if (index < 0 || index > len) { // If the index is out of range
        throw std::out_of_range("Index out of range");
    } else if (index == 0) {
        InsertHead(element);
    } else if (index == len) {
        InsertTail(element);
    } else {
        Node* newNode = CreateNode(element);
        Node* curr = FindByIndex(index);
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        len++;
    }
}

// Find node by index
Node* DoubleLinkList::FindByIndex(int index) const {
    if (index < 0 || index >= len) { // If the index is out of range
        throw std::out_of_range("Index out of range");
    }
    Node* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr;
}

// Update node value by index
void DoubleLinkList::UpdateNodeByIndex(int index, ElementType newValue) {
    Node* targetNode = FindByIndex(index);
    if (targetNode != nullptr) {
        targetNode->value = newValue;
    } else {
        throw std::runtime_error("Node not found");
    }
}

// Traverse from head
void DoubleLinkList::Travel(std::function<void(ElementType)> func) const {
    Node* curr = head;
    while (curr != nullptr) {
        func(curr->value);
        curr = curr->next;
    }
}

// Traverse from tail
void DoubleLinkList::ReTravel(std::function<void(ElementType)> func) const {
    Node* curr = tail;
    while (curr != nullptr) {
        func(curr->value);
        curr = curr->prev;
    }
}

// Remove node by index
void DoubleLinkList::RemoveByIndex(int index) {
    if (index < 0 || index >= len) {
        throw std::out_of_range("Index out of range");
    }
    Node* curr = FindByIndex(index);
    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    } else {
        head = curr->next;
    }
    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    } else {
        tail = curr->prev;
    }
    delete curr;
    len--;
}

// Remove node by value
void DoubleLinkList::RemoveByElement(ElementType element, std::function<bool(ElementType, ElementType)> func) {
    Node* curr = head;
    while (curr != nullptr) {
        if (func(curr->value, element)) {
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            } else {
                head = curr->next;
            }
            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            } else {
                tail = curr->prev;
            }
            delete curr;
            len--;
            return;
        }
        curr = curr->next;
    }
}

// Free all nodes
void DoubleLinkList::Free(std::function<void(ElementType)> func) {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        if (func) {
            func(temp->value);
        }
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Clear all nodes
void DoubleLinkList::Clear() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Find nodes by value
DoubleLinkList DoubleLinkList::FindByElement(ElementType element, std::function<bool(ElementType, ElementType)> func) const {
    DoubleLinkList result;
    Node* curr = head;
    while (curr != nullptr) {
        if (func(curr->value, element)) {
            result.InsertTail(curr->value);
        }
        curr = curr->next;
    }
    return result;
}

// Merge with another list
DoubleLinkList DoubleLinkList::Merge(const DoubleLinkList& other) const {
    DoubleLinkList result;
    Node* curr1 = head;
    while (curr1 != nullptr) {
        result.InsertTail(curr1->value);
        curr1 = curr1->next;
    }
    Node* curr2 = other.head;
    while (curr2 != nullptr) {
        result.InsertTail(curr2->value);
        curr2 = curr2->next;
    }
    return result;
}

// Reverse the list
void DoubleLinkList::Reverse() {
    Node* temp = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp != nullptr) {
        head = temp->prev;
    }
}

// Check if the list is empty
bool DoubleLinkList::IsEmpty() const {
    return len == 0;
}

// Get the length of the list
int DoubleLinkList::GetLength() const {
    return len;
}

// Get the head node
Node* DoubleLinkList::GetHead() const {
    return head;
}

// Get the tail node
Node* DoubleLinkList::GetTail() const {
    return tail;
}
