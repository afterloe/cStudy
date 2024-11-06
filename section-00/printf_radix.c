#include <stdio.h>

typedef int INT32;

int main(int argc, char** args) {
    INT32 num = 3;
    printf("十进制 num = %d\n", num);
    printf("八进制 num = %#o\n", num);
    printf("十六进制 num = %#x\n", num);
    return 0;
}
