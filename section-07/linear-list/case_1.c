#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arr
{
    // 数据域
    int num;

    // 指针域
    struct arr *next;
} Array;

void staticLinkedArr();

int main(int argc, char **args)
{
    staticLinkedArr();
    return 0;
}

/**
 * 静态链表
 */
void staticLinkedArr()
{
    Array d1 = {1};
    Array d2 = {11};
    Array d3 = {111};
    Array d4 = {10};
    Array d5 = {101};

    // 组链
    Array *head = NULL;
    head = &d1;
    d1.next = &d2;
    d2.next = &d3;
    d3.next = &d4;
    d4.next = &d5;

    // 遍历
    Array *foreach = NULL;
    foreach
        = head;
    while (foreach->next != NULL)
    {
        printf("value -> %d \n", foreach->num);
        foreach
            = foreach->next;
    }
}