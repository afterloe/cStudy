#include <stdio.h>

#ifndef SIZE
#define SIZE 10
#endif

// 编译时指定SIZE的值
// gcc case_0.c -DSIZE=11
/*
SIZE is 11
*/
int main(void)
{
    printf("SIZE is %d \n", SIZE);
    return 0;
}