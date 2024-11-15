#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int arr[10] = { 0, 1, 15, 34, 44, 59, 65, 73, 79, 99 };
    /*
        使用 折半查找算法 查询 数组中是否存在 59这个数字
    */
    int key = 59;
    int low, high, mid;
    low = 0; // 定义最低下标为数组 首位置
    high = sizeof(arr) / sizeof(arr[0]); // 定义最高下标为 数组 最后一个位置

    while(low <= high)
    {
        mid = (low + high) / 2; // 折半
        if (key < arr[mid])
        {
            // 若查找的值 比 中值 小
            high = mid - 1; // 最高位调整到 中位下标小1位
        }
        else if (key > arr[mid])
        {
            // 若查找的值 比 中值 大
            low = mid + 1; // 最低位 调整到 中位下标大1位
        }
        else
        {
            // return mid;
            break; // 相等则表示 mid就是 数据所在的下标
        }
    }

    printf("%d in arr[%d], val is %d \n", key, mid, arr[mid]);

    return 0;
}