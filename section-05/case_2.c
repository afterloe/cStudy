#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int *initArr(int);
void printArr(int *, int);
void sortAsc(int *, int);
void sortDesc(int *, int);

void doArr(int *p, int size, void (*handle)(int *, int))
{
    handle(p, size);
}

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

void sortDesc(int *p, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (*(p + j) < *(p + j + 1))
            {
                *(p + j + 1) = *(p + j) + *(p + j + 1);
                *(p + j) = *(p + j + 1) - *(p + j);
                *(p + j + 1) = *(p + j + 1) - *(p + j);
            }
        }
    }
}