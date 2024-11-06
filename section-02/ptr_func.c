#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main(int argc, char** argv) {
    int (*ptr)(int, int) = NULL;
    printf("%ld \n", sizeof(ptr));
    ptr = add;
    printf("%d \n", add(10, 11));
    printf("%d \n", ptr(10, 11));
    return 0;
}
