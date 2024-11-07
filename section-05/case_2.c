#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __CASE_2__
#define __CASE_2__
extern int *initArr(int);
extern void printArr(int *, int);
extern void sortAsc(int *, int);
extern void sortDesc(int *, int);
typedef void (*FUN_P)(int*, int);
#endif

void doArr(int *p, int size, FUN_P fun)
{
    fun(p, size);
}
/*
    通过对待排序序列从前向后（从下标较小的元素开始）,依次对相邻两个元素的值进行两两比较，
    若发现逆序则交换，使值较大的元素逐渐从前移向后部，就如果水底下的气泡一样逐渐向上冒。
*/
int main(int argc, char **argv)
{
    int size;
    printf("please input size of arr: ");
    scanf("%d", &size);
    int *arr = initArr(size);
    printf("befor sort \n");
    doArr(arr, size, printArr);
    printf("\n");
    printf("after sort \n");
    doArr(arr, size, sortDesc);
    doArr(arr, size, printArr);
    printf("\n");
    if (NULL != arr)
    {
        free(arr);
        arr = NULL;
    }
}

int *initArr(int size)
{
    int *p = calloc(size, size * sizeof(int));
    memset(p, 0, size * sizeof(int));
    for (int idx = 0; idx < size; idx++)
    {
        printf("input %d'num: ", idx + 1);
        scanf("%d", p + idx);
    }
    return p;
}

void printArr(int *p, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d \t", *(p + i));
    }
}

void sortAsc(int *p, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (*(p + j) > *(p + j + 1))
            {
                int tmp = *(p + j + 1);
                *(p + j + 1) = *(p + j);
                *(p + j) = tmp;
            }
        }
    }
}

/**
 * 不使用 第三个数 实现交换
 */
void sortDesc(int *p, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (*(p + j) < *(p + j + 1))
            {
                *(p + j + 1) += *(p + j);
                *(p + j) = *(p + j + 1) - *(p + j);
                *(p + j + 1) = *(p + j + 1) - *(p + j);
            }
        }
    }
}