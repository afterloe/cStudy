#include <stdio.h>
#include <stdlib.h>

void printArr(int* ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d \t", *ptr);
        ptr++;
    }
    printf("\n");
}

void test1() {
    int* ptr = NULL;
    ptr = (int*) malloc(5 * sizeof(int)); // 申请 int[5] 的空间大小
    int val = 10;
    for (int i = 0; i < 5; i++) {
        *(ptr+i) = val * i;
    }
    printArr(ptr, 5);
    free(ptr);
}

void test2() {
    int arr[5] = {1, 10, 100, 101, 201};
    int* ptr = NULL;
    ptr = arr;
    printArr(ptr, 5);
    for (int i = 0; i < 5; i++) {
        *(ptr+i) = 2 * i;
    }
    printArr(ptr, 5);
}

int main(int argc, char** argv) {
    test1();
    test2();
    return 0;
}
