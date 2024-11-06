#include <stdio.h>

void printIntArr(int*, int);
void printCharArr(char**, int);

int main(int argc, char** argv) {
    int arr[5] = {1, 2, 3, 11, 44};
    char* strArr[4] = {"hello", "world", "ubuntu", "one"};
    printIntArr(arr, sizeof(arr) / sizeof(arr[0]));
    printCharArr(strArr, sizeof(strArr) / sizeof(char*));
    return 0;
}

void printIntArr(int* ptr, int size) {
    int num = sizeof(ptr) / sizeof(int);
    printf("%d %d \n", num, size);
    for (int i = 0; i < size; i++) {
        printf("%d \n", *ptr);
        ptr++;
    }
    printf("\n");
}

void printCharArr(char** ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s \n", *ptr);
        ptr++;
    }
    printf("\n");
}
