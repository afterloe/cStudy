#include <stdio.h>

#ifndef __CASE_3__
#define __CASE_3__
void sort(int *, int);
#endif

/*
选择排序（ Selection sort）是一种简单直观的排序算法。
原理:
    每一趟从待排序的数据元素中选出最小（或最大）的一个元素，顺序放在已排好序的数列的最后，直到全部待排序的数据元素排完。
*/
int main(int argc, char **argv)
{
    int arr[5] = {10, 56, 2, 12, 8};
    int n = 5, j = 0, min;
    
    // 选择法排序
    for (int i = 0; i < n - 1; i++)
    {
        for (min = i, j = min + 1; j < n; j++)
        {
            if (arr[min] > arr[j])
                min = j;
        }

        if (min != i)
        {
            int tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }


    for (int idx = 0; idx < 5; idx++)
    {
        printf("%d \t", arr[idx]);
    }
    printf("\n");
    return 0;
}

/*
选择排序算法通过选择和交换来实现排序，其排序流程如下：
（1）首先从原始数组中选择最小的1个数据，将其和位于第1个位置的数据交换。
（2）接着从剩下的n-1个数据中选择次小的1个元素，将其和第2个位置的数据交换
（3）然后，这样不断重复，直到最后两个数据完成交换。最后，便完成了对原始数组的从小到大的排序。
*/
void sort(int *p, int size)
{
}