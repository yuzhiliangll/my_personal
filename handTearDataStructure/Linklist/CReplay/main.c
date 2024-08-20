#include <stdlib.h>
#include "LinkList.h"

int main() 
{
    Llist list;
    InitLinkList(&list);

    // 测试尾部插入
    InsertLinkTail(&list, 10);
    InsertLinkTail(&list, 20);
    InsertLinkTail(&list, 30);
    printf("链表内容 (尾部插入后): ");
    TravelLinkList(&list); // 应该输出: 10 20 30

    // 测试头部插入
    InsertHead(&list, 5);
    printf("链表内容 (头部插入后): ");
    TravelLinkList(&list); // 应该输出: 5 10 20 30

    // 测试按索引插入
    InsertByIndex(&list, 2, 15);
    printf("链表内容 (按索引插入后): ");
    TravelLinkList(&list); // 应该输出: 5 10 15 20 30

    // 测试按索引删除
    RemoveByIndex(&list, 3);
    printf("链表内容 (按索引删除后): ");
    TravelLinkList(&list); // 应该输出: 5 10 15 30

    // 测试按值删除
    RemoveByElement(&list, 10);
    printf("链表内容 (按值删除后): ");
    TravelLinkList(&list); // 应该输出: 5 15 30

    // 测试按索引更新
    UpdateByIndex(&list, 1, 25);
    printf("链表内容 (按索引更新后): ");
    TravelLinkList(&list); // 应该输出: 5 25 30

    // 测试按值更新
    UpdateByElement(&list, 25, 20);
    printf("链表内容 (按值更新后): ");
    TravelLinkList(&list); // 应该输出: 5 20 30

    // 测试查找
    ElementType* element = FindElementByIndex(&list, 1);
    if (element) {
        printf("索引 1 处的元素是: %d\n", *element); // 应该输出: 20
    }

    int* indices = FindElementByValue(&list, 30);
    printf("值为 30 的元素的索引: ");
    for (int i = 0; indices[i] != -1; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n"); // 应该输出: 2
    free(indices); // 释放内存

    // 测试是否存在元素
    if (IsHaveElement(&list, 5)) {
        printf("元素 5 存在于链表中\n");
    }

    // 测试链表反转
    Reserve(&list);
    printf("链表内容 (反转后): ");
    TravelLinkList(&list); // 应该输出: 30 20 5

    // 测试链表排序
    BubbleSort(&list);
    printf("链表内容 (排序后): ");
    TravelLinkList(&list); // 应该输出: 5 20 30

    // 测试链表去重
    InsertLinkTail(&list, 20);
    printf("链表内容 (插入重复元素后): ");
    TravelLinkList(&list); // 应该输出: 5 20 30 20

    Deduplicate(&list);
    printf("链表内容 (去重后): ");
    TravelLinkList(&list); // 应该输出: 5 20 30

    // 测试释放链表
    FreeLinkList(&list);
    printf("链表释放后，长度为: %d\n", GetLength(&list)); // 应该输出: 0

    return 0;
}
