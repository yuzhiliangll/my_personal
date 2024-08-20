#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Max_Size 20
#define ElementType int

struct Array {
    int arr[Max_Size];
    int len;
};

typedef struct Array Arr;

void InitArray(Arr *a);
bool InsertTail(Arr *a, ElementType value);
bool InsertHead(Arr *a, ElementType value);
bool InsertByIndex(Arr *a, int index, ElementType value);
bool UpdateValueByIndex(Arr *a, int index, ElementType value);
bool RemoveByIndex(Arr *a, int index);
bool RemoveByElement(Arr *a, ElementType value);
ElementType* FindElementByIndex(Arr *a, int index);
int* FindElementByValue(Arr *a, ElementType value);
void ArraySort(Arr *a, int start, int end);
void Deduplicate(Arr *a);
Arr GetInsection(Arr *a1, Arr *a2);
Arr GetUnionSet(Arr *a1, Arr *a2);
Arr Merge(Arr *a1, Arr *a2);
int BinarySearch(Arr *a, ElementType key, int low, int high);

void InitArray(Arr *a) {
    memset(a->arr, 0, Max_Size * sizeof(ElementType));
    a->len = 0;
}

bool InsertTail(Arr *a, ElementType value) {
    if (a->len >= Max_Size) {
        printf("Array is full! Failed to insert.\n");
        return false;
    }
    a->arr[a->len++] = value;
    return true;
}

bool InsertHead(Arr *a, ElementType value) {
    if (a->len >= Max_Size) {
        printf("Array is full! Failed to insert.\n");
        return false;
    }
    for (int i = a->len; i > 0; i--) {
        a->arr[i] = a->arr[i - 1];
    }
    a->arr[0] = value;
    a->len++;
    return true;
}

bool InsertByIndex(Arr *a, int index, ElementType value) {
    if (index < 0 || index > a->len || a->len >= Max_Size) {
        printf("Index is out of range or array is full! Failed to insert.\n");
        return false;
    }
    for (int i = a->len; i > index; i--) {
        a->arr[i] = a->arr[i - 1];
    }
    a->arr[index] = value;
    a->len++;
    return true;
}

bool UpdateValueByIndex(Arr *a, int index, ElementType value) {
    if (index < 0 || index >= a->len) {
        printf("Index is out of range! Failed to update.\n");
        return false;
    }
    a->arr[index] = value;
    return true;
}

bool RemoveByIndex(Arr *a, int index) {
    if (index < 0 || index >= a->len) {
        printf("Index is out of range! Failed to remove.\n");
        return false;
    }
    for (int i = index; i < a->len - 1; i++) {
        a->arr[i] = a->arr[i + 1];
    }
    a->len--;
    return true;
}

bool RemoveByElement(Arr *a, ElementType value) {
    int i;
    for (i = 0; i < a->len; i++) {
        if (a->arr[i] == value) {
            break;
        }
    }
    if (i == a->len) {
        return false;
    }
    return RemoveByIndex(a, i);
}

ElementType* FindElementByIndex(Arr *a, int index) {
    if (index < 0 || index >= a->len) {
        printf("Index is out of range!\n");
        return NULL;
    }
    return &a->arr[index];
}

int* FindElementByValue(Arr *a, ElementType value) {
    int *p = (int *)malloc((a->len + 1) * sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < a->len; i++) {
        if (a->arr[i] == value) {
            p[count++] = i;
        }
    }
    p[count] = -1;
    return p;
}

void ArraySort(Arr *a, int start, int end) {
    if (start >= end) {
        return;
    }

    int left = start;
    int right = end;
    int temp = a->arr[left];

    while (left < right) {
        while (a->arr[right] >= temp && left < right) {
            right--;
        }
        a->arr[left] = a->arr[right];

        while (a->arr[left] <= temp && left < right) {
            left++;
        }
        a->arr[right] = a->arr[left];
    }
    a->arr[left] = temp;

    ArraySort(a, start, left - 1);
    ArraySort(a, left + 1, end);
}

void Deduplicate(Arr *a) {
    ArraySort(a, 0, a->len - 1);
    for (int i = 1; i < a->len; i++) {
        if (a->arr[i] == a->arr[i - 1]) {
            RemoveByIndex(a, i);
            i--;
        }
    }
}

Arr GetInsection(Arr *a1, Arr *a2) {
    Arr c;
    InitArray(&c);
    for (int i = 0; i < a1->len; i++) {
        for (int j = 0; j < a2->len; j++) {
            if (a1->arr[i] == a2->arr[j]) {
                int *p = FindElementByValue(&c, a1->arr[i]);
                if (p == NULL || p[0] == -1) {
                    InsertTail(&c, a1->arr[i]);
                }
                if (p != NULL) {
                    free(p);
                }
            }
        }
    }
    return c;
}

Arr GetUnionSet(Arr *a1, Arr *a2) {
    Arr UnionSet;
    InitArray(&UnionSet);
    for (int i = 0; i < a1->len; i++) {
        InsertTail(&UnionSet, a1->arr[i]);
    }
    for (int i = 0; i < a2->len; i++) {
        InsertTail(&UnionSet, a2->arr[i]);
    }
    Deduplicate(&UnionSet);
    return UnionSet;
}

Arr Merge(Arr *a1, Arr *a2) {
    ArraySort(a1, 0, a1->len - 1);
    ArraySort(a2, 0, a2->len - 1);
    int i = 0, j = 0;
    Arr result;
    InitArray(&result);
    while (i < a1->len && j < a2->len) {
        if (a1->arr[i] <= a2->arr[j]) {
            InsertTail(&result, a1->arr[i]);
            i++;
        } else {
            InsertTail(&result, a2->arr[j]);
            j++;
        }
    }
    while (i < a1->len) {
        InsertTail(&result, a1->arr[i]);
        i++;
    }
    while (j < a2->len) {
        InsertTail(&result, a2->arr[j]);
        j++;
    }
    return result;
}

int BinarySearch(Arr *a, ElementType key, int low, int high) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (key < a->arr[mid]) {
        return BinarySearch(a, key, low, mid - 1);
    } else if (key > a->arr[mid]) {
        return BinarySearch(a, key, mid + 1, high);
    } else {
        return mid;
    }
}

int main() 
{
    Arr array1, array2, result;
    InitArray(&array1);
    InitArray(&array2);

    printf("测试插入操作:\n");
    InsertTail(&array1, 5);
    InsertTail(&array1, 3);
    InsertTail(&array1, 8);
    InsertHead(&array1, 2);
    InsertByIndex(&array1, 2, 6);
    for (int i = 0; i < array1.len; i++) 
    {
        printf("%d ", array1.arr[i]);
    }
    printf("\n\n");

    printf("测试删除操作:\n");
    RemoveByIndex(&array1, 2);
    RemoveByElement(&array1, 8);
    for (int i = 0; i < array1.len; i++) 
    {
        printf("%d ", array1.arr[i]);
    }
    printf("\n\n");

    printf("测试查找操作:\n");
    ElementType* elem = FindElementByIndex(&array1, 1);
    if (elem != NULL) {
        printf("索引1处的元素为: %d\n", *elem);
    }
    int* indices = FindElementByValue(&array1, 3);
    if (indices != NULL && indices[0] != -1) {
        printf("值为3的元素索引: ");
        for (int i = 0; indices[i] != -1; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
    }
    free(indices);
    printf("\n");

    printf("测试排序操作:\n");
    InsertTail(&array1, 7);
    InsertTail(&array1, 4);
    ArraySort(&array1, 0, array1.len - 1);
    for (int i = 0; i < array1.len; i++) {
        printf("%d ", array1.arr[i]);
    }
    printf("\n\n");

    printf("测试去重操作:\n");
    InsertTail(&array1, 4);
    Deduplicate(&array1);
    for (int i = 0; i < array1.len; i++) {
        printf("%d ", array1.arr[i]);
    }
    printf("\n\n");

    printf("测试求交集、并集和合并操作:\n");
    InsertTail(&array2, 3);
    InsertTail(&array2, 7);
    InsertTail(&array2, 9);

    result = GetInsection(&array1, &array2);
    printf("交集: ");
    for (int i = 0; i < result.len; i++) {
        printf("%d ", result.arr[i]);
    }
    printf("\n");

    result = GetUnionSet(&array1, &array2);
    printf("并集: ");
    for (int i = 0; i < result.len; i++) {
        printf("%d ", result.arr[i]);
    }
    printf("\n");

    result = Merge(&array1, &array2);
    printf("合并: ");
    for (int i = 0; i < result.len; i++) {
        printf("%d ", result.arr[i]);
    }
    printf("\n\n");

    printf("测试二分查找:\n");
    int index = BinarySearch(&array1, 5, 0, array1.len - 1);
    if (index != -1) {
        printf("元素5的索引为: %d\n", index);
    } else {
        printf("未找到元素5\n");
    }

    return 0;
}
