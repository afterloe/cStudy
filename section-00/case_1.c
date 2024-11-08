#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef __CASE_1__
#define __CASE_1__
#define MAX_NUM 100

extern int generatorNum();
extern void test1();
extern void test2();

#endif

int main() {
    // 初始化随即种子
    srand(time(NULL));

    test1();
    test2();
    return 0;
}

// 生成指定范围的 随机数
int generatorNum() {
    return rand() % MAX_NUM + 1;
}

/*
 * 方法1: 加法 
 */
void test1() {
    printf("方法1 - 加法 \n");
    int a = generatorNum(), b = generatorNum();
    printf("before\t%d - %d \n", a, b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("after\t%d - %d \n", a, b);
}

/*
 * 方法2： 使用位操作  按位 异或
 */
void test2() {
    printf("方法2 - 按位异或\n");
    int a = generatorNum(), b = generatorNum();
    printf("before\t%d -%d \n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("before\t%d -%d \n", a, b);
}