#include "DoubleLinkList.h"


// 初始化双向链表
void InitDLlist(DLlist *list)// initialize the list
{
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

// 创建新节点
node* CreateNode(ElementType element)// create a node with element
{
    node* newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        perror("Failed to create a new node");
        exit(EXIT_FAILURE);// 程序以失败状态终止（通常值为 1）
    }
    newNode->value = element;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


// 尾插
void InsertDLlistTail(DLlist *list, ElementType element)// insert a node with element at the end of the list
{
    node* newNode = CreateNode(element);
    if (list->tail == NULL)// if the list is empty
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;// update the tail pointer
    }
    list->len++;
}

// 头插
void InsertDLlistHead(DLlist *list, ElementType element)// insert a node with element at the beginning of the list
{
    node* newNode = CreateNode(element);
    if (list->head == NULL)// if the list is empty
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;// update the head pointer
    }
    list->len++;
}

// 按索引插入
void InsertByIndex(DLlist *list, int index, ElementType element)
{
    if (index < 0 || index > list->len)// if the index is out of range
    {
        perror("Index out of range");
        return;
    }
    else if (index == 0)// if the index is 0, insert at the head
    {
        InsertDLlistHead(list, element);
        return;
    }
    else if (index == list->len)// if the index is the length of the list, insert at the tail
    {
        InsertDLlistTail(list, element);
        return;
    }
    else// if the index is in the middle of the list
    {
        node* newNode = CreateNode(element);// create a new node
        node* curr = FindByIndex(list, index);// find the node at the index
        newNode->next = curr;// update the pointers
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        list->len++;
    }
}   

// 新增: 按索引查找节点
node* FindByIndex(DLlist *list, int index)
{
    if (index < 0 || index >= list->len)// if the index is out of range
    {
        perror("Index out of range");
        return NULL;
    }
    node* curr = list->head;// start from the head
    for (int i = 0; i < index; i++)// iterate to the index
    {
        curr = curr->next;// update the current node
    }
    return curr;// return the current node
}

// 新增: 更新节点值
void UpdateNodeByIndex(DLlist *list, int index, ElementType newValue)
{
    node* targetNode = FindByIndex(list, index);// find the node at the index
    if (targetNode != NULL) // if the node is found
    {
        targetNode->value = newValue;// update the value
    }
    else
    {
        perror("Node not found");
    }
}

void Travel(DLlist *list, void (*funcptr)(ElementType))
{
    node* curr = list->head;
    while (curr != NULL)
    {
        funcptr(curr->value);// call the function pointer
        printf("curr->value: %d\n", curr->value);
        curr = curr->next;// update the current node
    }
}

void ReTravel(DLlist *list, void (*funcptr)(ElementType))
{
    node* curr = list->tail;
    while (curr != NULL)
    {
        funcptr(curr->value);// call the function pointer
        printf("curr->value: %d\n", curr->value);
        curr = curr->prev;// update the current node
    }
}

// 按索引删除
void RemoveByIndex(DLlist *list, int index)
{
    if (index < 0 || index >= list->len)
    {
        perror("Index out of range");
        return;
    }
    node* curr = FindByIndex(list, index);
    if  (curr->prev != NULL)// if the node is not the first node
    {
        curr->prev->next = curr->next;
    }
    else
    {
        list->head = curr->next;// update the head node
    }

    if (curr->next != NULL)// if the node is not the last node
    {
        curr->next->prev = curr->prev;// update the previous node of the next node
    }
    else
    {
        list->tail = curr->prev;// update the tail node
    }
    free(curr);// free the memory of the current node
    list->len--;// update the length of the list

}

// 按值删除
/*
    list: 指向链表的指针。
    element: 需要删除的元素。
    funcptr: 指向比较函数的指针，用于比较元素是否相等。
*/
void RemoveByElement(DLlist *list, ElementType element, bool (*funcptr)(ElementType, ElementType))
{
    node* curr = list->head;
    while (curr != NULL) 
    {
        if (funcptr(curr->value, element)) // 通过调用 funcptr 比较当前节点的值和目标值 element，如果匹配，则进入删除节点的流程。
        {
            if (curr->prev != NULL) // 处理前驱节点
            /*
                如果当前节点有前驱节点，则将前驱节点的 next 指针指向当前节点的后继节点。
                否则，如果当前节点是头节点，则更新链表的 head 指针。
            */
            {
                curr->prev->next = curr->next;
            } 
            else 
            {
                list->head = curr->next;
            }

            // 处理后继节点:
            /*
                如果当前节点有后继节点，则将后继节点的 prev 指针指向当前节点的前驱节点。
                否则，如果当前节点是尾节点，则更新链表的 tail 指针。
            */
            if (curr->next != NULL) 
            {
                curr->next->prev = curr->prev;
            } 
            else {
                list->tail = curr->prev;// 
            }
            free(curr);
            list->len--;
            return;
        }
        curr = curr->next;
    }
    /*
        注意事项
        函数指针 funcptr 必须正确实现，用于比较两个 ElementType 值，否则可能导致删除失败。
        内存管理: 在删除节点后，确保不再访问已释放的内存。
    */
}

// 释放
/*
    功能: 释放链表中的所有节点，
    同时提供了一个可选的回调函数，用于在释放节点之前执行某些特定的操作。
*/
/*
    分析:

回调函数 funcptr:
如果传入了回调函数 funcptr，则在释放节点内存之前，会对节点的值 temp->value 进行处理。这通常用于处理节点的值涉及到动态分配的内存，需要在释放节点前进行特定的清理工作。
如果 funcptr 为 NULL，则不会执行任何处理，只释放节点内存。
释放节点:
每个节点都会被 free，彻底释放内存。
最后将链表的 head、tail 指针设为 NULL，并将 len 置为 0，表示链表被完全释放。
*/
void FreeDLlist(DLlist *list, void (*funcptr)(ElementType))
{
    node* curr = list->head;
    while (curr != NULL)
    {
        node* temp = curr;
        curr = curr->next;
        if (funcptr != NULL)// 如果传入了回调函数
        {
            funcptr(temp->value);// 在释放节点前，对节点的值进行某些操作
        }
        free(temp);// 释放节点
    }
    list->head = NULL; // 清空链表头指针
    list->tail = NULL;
    list->len = 0;
}

// 新增: 清空链表 但不释放节点内存
// 清空链表中的所有节点，但不提供对节点值的处理，也不提供回调函数。
void ClearDLlist(DLlist *list)
{
    node* curr = list->head;
    while (curr != NULL)
    {
        node* temp = curr;
        curr = curr->next;
        free(temp);// 直接释放节点内存
    }
    list->head = NULL;// 清空链表头指针
    list->tail = NULL;
    list->len = 0;
}
/*
    区别总结
回调函数:

FreeDLlist 提供了一个可选的回调函数 funcptr，用于在释放节点之前处理节点的值。这在处理需要特殊清理的节点时很有用。
ClearDLlist 不提供回调函数，直接释放节点内存，不对节点值进行任何处理。
用途:

FreeDLlist 适用于需要对节点值进行额外处理的场景，如节点值涉及动态分配的内存，或者需要执行某些特定操作。
ClearDLlist 适用于简单的链表清空操作，只是释放节点的内存，不关心节点值的处理。
内存管理:

如果节点的值涉及动态分配的内存，使用 ClearDLlist 可能会导致内存泄漏，而 FreeDLlist 可以通过回调函数避免这种情况。
示例应用场景
FreeDLlist:

假设链表的节点值是指向某种复杂数据结构的指针，且该数据结构占用大量内存。在释放节点前，需要先释放这些结构占用的内存。这时，使用 FreeDLlist 并传入适当的回调函数非常有用。
ClearDLlist:

如果链表的节点值是简单的数据类型（如整数），或值不涉及动态分配的内存，则 ClearDLlist 足以完成任务。
*/

DLlist FindByElement(DLlist *list, ElementType element, bool (*funcPtr)(ElementType, ElementType))
{
    DLlist result;
    InitDLlist(&result);
    node* curr = list->head;
    while (curr != NULL) 
    {
        if (funcPtr(curr->value, element)) 
        {
            InsertDLlistTail(&result, curr->value);
        }
        curr = curr->next;
    }
    return result;
}

// 合并链表
DLlist MergeDLlist(DLlist *list1, DLlist *list2)
{
    DLlist result;
    InitDLlist(&result);
    
    node* curr1 = list1->head;
    while (curr1 != NULL) 
    {
        InsertDLlistTail(&result, curr1->value);
        curr1 = curr1->next;
    }
    
    node* curr2 = list2->head;
    while (curr2 != NULL) 
    {
        InsertDLlistTail(&result, curr2->value);
        curr2 = curr2->next;
    }
    
    return result;
}

// 反转链表
void ReverseDLlist(DLlist *list)
{
    node* temp = NULL;
    node* curr = list->head;
    while (curr != NULL) 
    {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp != NULL) 
    {
        list->head = temp->prev;
    }
}

// 新增: 判断链表是否为空
bool IsEmpty(DLlist *list)
{
    return list->len == 0;
}

// 获取链表长度
int GetDLlistLength(DLlist *list)
{
    return list->len;
}

// 获取头节点
node* GetDLlistHead(DLlist *list)
{
    return list->head;
}

// 获取尾节点
node* GetDLlistTail(DLlist *list)
{
    return list->tail;
}



