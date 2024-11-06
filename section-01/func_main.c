#include <stdio.h>
#include <func.h>

// 调用函数
int main(int argc, char *argv[]) {
    int a = 60, b = 40;
    const int max_num = max(a, b);
    printf("max is %d\n", max_num);
    return 0;
}
