#include "DoubleLinkList.h"

// 定义一个简单的打印函数，用于遍历链表时打印元素
void PrintElement(ElementType element) {
    printf("%d ", (int)element);  // 将 void* 类型转换为 int 类型
}

// 比较两个元素是否相等的函数
bool CompareElement(ElementType a, ElementType b) {
    return (int)a == (int)b;
}

int main() {
    DLlist list;
    InitDLlist(&list);

    // 插入元素
    InsertDLlistTail(&list, (void *)1);  // 将 int 转换为 void* 类型
    InsertDLlistTail(&list, (void *)2);
    InsertDLlistTail(&list, (void *)3);

    // 测试遍历链表
    printf("Original List: ");
    Travel(&list, PrintElement);  // 预期输出: 1 2 3
    printf("\n");

    // 在索引 2 处插入值 9
    InsertByIndex(&list, 2, (void *)9);

    // 测试遍历链表
    printf("After Inserting 9 at Index 2: ");
    Travel(&list, PrintElement);  // 预期输出: 1 2 9 3
    printf("\n");

    // 测试按值删除
    RemoveByElement(&list, (void *)1, CompareElement);

    // 测试遍历链表
    printf("After Removing 1: ");
    Travel(&list, PrintElement);  // 预期输出: 2 9 3
    printf("\n");

    // 查找索引为 1 的节点
    node *foundNode = FindByIndex(&list, 1);
    printf("Found Node at Index 1: %d\n", (int)(foundNode->value));  // 预期输出: 9

    // 创建第二个链表并合并
    DLlist list2;
    InitDLlist(&list2);
    InsertDLlistTail(&list2, (void *)4);
    InsertDLlistTail(&list2, (void *)5);

    DLlist mergedList = MergeDLlist(&list, &list2);

    // 测试遍历合并后的链表
    printf("Merged List: ");
    Travel(&mergedList, PrintElement);  // 预期输出: 2 9 3 4 5
    printf("\n");

    // 释放链表
    FreeDLlist(&list, NULL);
    FreeDLlist(&list2, NULL);
    FreeDLlist(&mergedList, NULL);

    return 0;
}

