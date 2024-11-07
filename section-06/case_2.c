#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 防止文件重复包含
#ifndef __ARRAY__
#define __ARRAY__
typedef struct arr
{
    int data;

    struct arr *next;
} Array;

extern Array *insert(Array *, const Array);
extern void release(Array *);
extern void printArr(Array *);

#endif

int main(int argc, char **argv)
{
    Array *arr = NULL;
    while (1)
    {
        char cmd[5] = "";
        printf("intpu your cmd \n");
        scanf("%s", cmd);
        if (strcmp(cmd, "e") == 0)
        {
            printf("bye! \n");
            release(arr);
            break;
        }
        else if (strcmp(cmd, "i") == 0)
        {
            Array a;
            printf("input data: ");
            scanf("%d", &a.data);
            arr = insert(arr, a);
        }
        else if (strcmp(cmd, "p") == 0)
        {
            printArr(arr);
        }
        else
        {
            printf("unknow cmd, supper e -> exit; i -> insert; p -> printf \n");
        }
    }
    return 0;
}

void release(Array *foreach)
{
    if (NULL == foreach)
    {
        return;
    }
    free(foreach);
    foreach
        == NULL;
}

Array *insert(Array *foreach, const Array data)
{
    Array *next = malloc(sizeof(Array));
    *next = data;
    next->next = NULL;

    if (NULL != foreach)
    {
        next->next = foreach;
    }

    foreach
        = next;
}

void printArr(Array *foreach)
{
    if (NULL == foreach)
    {
        printf("Array is empty \n");
        return;
    }

    while (foreach != NULL)
    {
        printf("%d \t", foreach->data);
        foreach
            = foreach->next;
    }
    printf("\n");
}
