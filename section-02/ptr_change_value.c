#include <stdio.h>

void findMax(int, int, int*);

int main(int argc, char** args) {
    int a = 0, b = 10, max;
    findMax(a, b, &max);
    printf("max value = %d \n", max);
    b = 100;
    printf("max value = %d \n", max);
    return 0;
}

void findMax(int a, int b, int* max) {
    if (a > b) {
        *max = a;
    } else {
        *max = b;
    }
}
