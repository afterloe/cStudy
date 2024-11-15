#include <stdio.h>
#include <stdlib.h>

void ProduceFib(int* fib, int size)
{
    int i;
    fib[0] = 1;
    fib[1] = 1;
    for (i = 2; i < size; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main(int argc, char** argv)
{
    int* F = calloc(10, sizeof(int)); // 生成一个斐波纳切 数列
    ProduceFib(F, 10);

    int arr[10] = { 0, 1, 15, 34, 44, 59, 65, 73, 79, 99 };
    int* idx = NULL;

    int key = 15, n = sizeof(arr) / sizeof(arr[0]);

    int low, high, mid, i, k;
    low = 0;
    high = n;
    k = 0;
    
    while (n > F[k] - 1) // 计算n位于 斐波纳切数列的位置
    {
        k++;
    }

    for (i = n; i < F[k] - 1; i++) // 将不满的数值补全
    {
        arr[i] = arr[n];
    }

    while (low <= high)
    {
        mid = low + F[k - 1] - 1; // 计算当前分割的下标
        if (key < arr[mid]) // 若查找记录 小于当前分割的记录
        {
            high = mid - 1; // 最高下条
            k = k - 1; // F下标减1位
        }
        else if (key > arr[mid])
        {
            low = mid + 1;
            k = k - 2; // F下标减2位
        }
        else
        {
            if (mid <= n)
            {
                idx = &mid; // 若相等则说明mid中为
            }
            else
            {
                idx = &n;
            }
            break;
        }
    }

    printf("value %d in arr[%d] \n", key, *idx);
    free(F);
    F = NULL;
    idx = NULL;

    return EXIT_SUCCESS;
}