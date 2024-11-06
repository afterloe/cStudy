#include <stdio.h>

int add (int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int calc(int a, int b, int (*func)(int, int)) {
    return func(a, b);
}

int main(int argc, char** argv) {
    printf("add - > %d \n", calc(10, 20, add));
    printf("sub - > %d \n", calc(10, 20, sub));
}
