#include "LinkList.h"

// 链表初始化
void InitLinkList(Llist *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

node* CreateNode(ElementType element)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        printf("Memory allocation error!\n");
        return NULL;
    }

    newNode->value = element;
    newNode->next = NULL;
    return newNode;
}

// 链表遍历
void TravelLinkList(Llist *list)// 从头结点开始依次访问每个节点--通常用于打印
{
    printf("List length: %d\n", list->len);
    node *travelsalPoint = list->head;
    while (travelsalPoint != NULL)
    {
        printf("%d ", travelsalPoint->value);// 打印节点值
        travelsalPoint = travelsalPoint->next;// 指针后移
    }
    printf("\n");
}

// 链表尾部插入
bool InsertLinkTail(Llist *list, ElementType element)
{
    node *newNode = CreateNode(element);
    if (newNode == NULL) return false;

    if(list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        node *travelsalPoint = list->head;
        while(travelsalPoint->next != NULL)// 找到链表尾部
        {
            travelsalPoint = travelsalPoint->next;// 指针后移
        }
        travelsalPoint->next = newNode;// 将新节点插入到链表尾部
    }
    list->len++;// 更新长度
    return true;
}

// 链表头部插入
bool InsertHead(Llist *list, ElementType element)
{
    node *newNode = CreateNode(element);
    if (newNode == NULL) return false;

    newNode->next = list->head;// 将新节点插入到链表头部
    list->head = newNode; // 更新头部
    list->len++;// 更新长度
    return true;
}

// 链表按索引插入
bool InsertByIndex(Llist *list, int index, ElementType element)
{
    if (index < 0 || index >= list->len)// 判断索引是否合法---很重要
    {
        printf("Illegal index\n");
        return false;
    }
    if (index == 0)// 头部插入
    {
        return InsertHead(list, element);
    }
    // 中间插入
    
    node *newNode = CreateNode(element);// 创建新节点
    if (newNode == NULL) return false;
    node *travelsalPoint = list->head;// 遍历指针的节点

    for (int i = 1; i < index; i++)// 找到插入位置的前一个节点
    {
        travelsalPoint = travelsalPoint->next;// 指针后移
    }
    newNode->next = travelsalPoint->next;// 将新节点插入到链表中
    travelsalPoint->next = newNode;
    list->len++;// 更新长度
    return true;
}

// 链表按索引删除
bool RemoveByIndex(Llist *list, int index)
{
    if (index < 0 || index >= list->len)// 判断索引是否合法---很重要
    {
        printf("Illegal index\n");
        return false;
    }
    
    node *travelsalPoint = list->head;// 遍历指针的节点
    if (index == 0)// 头部删除
    {
        list->head = list->head->next;
        free(travelsalPoint);
    }
    // 中间删除
    else
    {
        for(int i = 1; i < index; i++)// 找到删除位置的前一个节点
        {
            travelsalPoint = travelsalPoint->next;// 指针后移
        }
        node *toFree = travelsalPoint->next;// 保存要删除的节点
        travelsalPoint->next = toFree->next;// 将要删除的节点从链表中移除
        free(toFree);// 释放内存
    }
    list->len--;
    return true;
}

// 链表按值删除
bool RemoveByElement(Llist *list, ElementType element)
{
    node *travelsalPoint = list->head;// 遍历指针的节点
    node *pre = NULL;// 前一个节点

    while (travelsalPoint != NULL)
    {
        if (travelsalPoint->value == element)// 找到要删除的节点
        {
            if (pre == NULL)// 头节点---头部删除
            {
                list->head = travelsalPoint->next;// 将头节点指向下一个节点
            }
            else// 中间删除
            {
                pre->next = travelsalPoint->next;
            }
            node *toFree = travelsalPoint;// 保存要删除的节点
            travelsalPoint = travelsalPoint->next;
            free(toFree);// 释放内存
            list->len--;
        }
        else
        {
            pre = travelsalPoint;// 更新前一个节点
            travelsalPoint = travelsalPoint->next;// 指针后移
        }
    }
    return true;
}

// 链表按索引更新
bool UpdateByIndex(Llist *list, int index, ElementType element)
{
    if (index < 0 || index >= list->len)
    {
        printf("Illegal index\n");
        return false;
    }

    node *traversalPoint = list->head;
    for (int i = 0; i < index; i++)
    {
        traversalPoint = traversalPoint->next;
    }
    traversalPoint->value = element;
    return true;
}

// 链表按值更新
bool UpdateByElement(Llist *list, ElementType oldValue, ElementType newValue)
{
    node *traversalPoint = list->head;
    bool updated = false;// 记录是否更新过

    while (traversalPoint != NULL)
    {
        /* code */
        if(traversalPoint->value == oldValue)// 找到要更新的
        {
            traversalPoint->value = newValue;
            updated = true;// 更新过
        }
        traversalPoint = traversalPoint->next;// 指针后移
    }
    return updated;
}

// 按索引查找元素
ElementType* FindElementByIndex(Llist *list, int index)
{
    if (index < 0 || index >= list->len)// 判断位置是否合法
    {
        printf("Illegal index\n");
        return NULL;
    }

    node *traversalPoint = list->head;
    for (int i = 0; i < index; i++)
    {
        traversalPoint = traversalPoint->next;
    }
    return &(traversalPoint->value);
}

// 按值查找元素
int* FindElementByValue(Llist *list, ElementType element)// 查找返回所有匹配指定值的节点的索引
{
    int *arr = (int *)malloc(sizeof(int) * (list->len + 1));// 分配内存

    if(arr == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    node *traversalPoint = list->head;
    int k = 0;// 记录匹配的节点个数
    for (int i = 0; i < list->len; i++)
    {
        if(traversalPoint->value == element)
        {
            arr[k++] = i;// 记录匹配的节点索引
        }
        traversalPoint = traversalPoint->next;// 指针后移
    }
    arr[k] = -1;// 结束标志
    return arr;
}

// 判断是否存在指定元素
/*
    遍历整个数组: 使用循环遍历 indices 数组，检查是否有匹配的元素。
    提前退出: 一旦找到匹配的元素，可以通过 break 提前退出循环，提高效率。
    释放内存: 在使用完 indices 后释放内存，防止内存泄漏。
*/
bool IsHaveElement(Llist *list, ElementType element)
{
    int *indices = FindElementByValue(list, element);
    if (indices == NULL) return false;

    bool found = false;
    for (int i = 0; indices[i] != -1; i++) 
    {
        found = true;
        break; // 找到匹配的元素后可以提前退出循环
    }

    free(indices); // 释放内存
    return found;
}

// 判断链表是否为空
bool IsEmpty(Llist *list)
{
    return list->len == 0;// 链表长度为0，则链表为空
}

// 链表冒泡排序
void BubbleSort(Llist *list)
{
    for (int i = 0; i < list->len - 1; i++) 
    {
        node *traversalPoint = list->head;
        for (int j = 0; j < list->len - i - 1; j++) 
        {
            if (traversalPoint->value > traversalPoint->next->value) 
            {
                ElementType temp = traversalPoint->value;
                traversalPoint->value = traversalPoint->next->value;
                traversalPoint->next->value = temp;
            }
            traversalPoint = traversalPoint->next;
        }
    }
}

// 获取链表交集
Llist GetInsection(Llist *list1, Llist *list2)// 交集中的元素顺序可以不保留
{
    Llist insection;
    InitLinkList(&insection);// 初始化交集链表

    for (int i = 0; i < list1->len; i++) 
    {
        ElementType value1 = *FindElementByIndex(list1, i);// 获取链表1的元素
        if (IsHaveElement(list2, value1) && !IsHaveElement(&insection, value1)) // 判断链表2中是否有该元素，并且该元素不在交集链表中
        {
            InsertLinkTail(&insection, value1);// 将元素插入到交集链表尾部
        }
    }
    return insection;
}

void Deduplicate(Llist *list)
{
    BubbleSort(list);

    node *traversalPoint = list->head;
    while (traversalPoint != NULL && traversalPoint->next != NULL) 
    {
        if (traversalPoint->value == traversalPoint->next->value) 
        {
            node *toFree = traversalPoint->next;
            traversalPoint->next = toFree->next;
            free(toFree);
            list->len--;
        } 
        else 
        {
            traversalPoint = traversalPoint->next;
        }
    }
}

// 获取链表并集
Llist GetUnionSet(Llist *list1, Llist *list2)// 包含两个链表的所有元素，去重后形成新的链表
{
    Llist unionSet;
    InitLinkList(&unionSet);

    for (int i = 0; i < list1->len; i++) 
    {
        InsertLinkTail(&unionSet, *FindElementByIndex(list1, i));
    }

    for (int i = 0; i < list2->len; i++) 
    {
        if (!IsHaveElement(&unionSet, *FindElementByIndex(list2, i))) 
        {
            InsertLinkTail(&unionSet, *FindElementByIndex(list2, i));
        }
    }
    return unionSet;
}

// 合并两个链表
Llist Merge(Llist *list1, Llist *list2)// 添加到list1 的尾部形成新的链表
{
    // 如果 list1 为空，返回 list2
    if (list1->len == 0) {
        return *list2;
    }
    
    // 如果 list2 为空，返回 list1
    if (list2->len == 0) {
        return *list1;
    }

    // 找到 list1 的尾节点
    node *tail1 = list1->head;
    while (tail1->next != NULL) {
        tail1 = tail1->next;
    }

    // 将 list2 的头节点添加到 list1 的尾部
    tail1->next = list2->head; // 跳过 list2 的头节点
    list1->len += list2->len; // 更新 list1 的长度

    // 返回合并后的链表
    return *list1;
}

// 链表反转
bool Reserve(Llist *list)
{
    if (list->head == NULL || list->head->next == NULL)
    {
        return true; // No need to reverse if the list is empty or has only one node
    }

    node *prev = NULL;
    node *current = list->head;
    node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
    return true;
}

// 链表递归反转
node* ReserveRecursion(node *n) // 通过递归方式, 返回新的头节点
{
    // 基本情况：如果链表为空或只有一个节点，则返回该节点
    if (n == NULL || n->next == NULL) {
        return n;
    }

    // 递归反转链表的其余部分
    node *newHead = ReserveRecursion(n->next);//以反转链表的其余部分，并返回反转后的新头节点 newHead。

    // 将当前节点 n 的下一个节点的 next 指向当前节点 n
    n->next->next = n;

    // 将当前节点的 next 设为 NULL，避免形成环
    n->next = NULL;

    // 返回新的头节点
    return newHead;
}

// 释放链表
void FreeLinkList(Llist *list)// 释放链表中的所有节点
{
    node *traversalPoint = list->head;
    while (traversalPoint != NULL)
    {
        node *temp = traversalPoint;// 保存当前节点
        traversalPoint = traversalPoint->next;// 移动到下一个节点
        free(temp);// 释放当前节点
    }
    list->head = NULL;
    list->len = 0;
}

// 链表长度
int GetLength(Llist *list)
{
    return list->len;
}
