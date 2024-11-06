#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* getAddr(int);
void loadVal(int*, int);
void printArr(int*, int);

int main(int argc, char** argv) {
    int size;
    printf("please input num what you want \n");
    scanf("%d", &size);
    int* ptr = getAddr(size);
    memset(ptr, 0, sizeof(int));
    loadVal(ptr, size);
    printArr(ptr, size);
    free(ptr);
    return 0;
}

int* getAddr(int size) {
    return (int*)malloc(size * sizeof(int));
}

void loadVal(int* p, int size) {
    for (int i = 0; i < size; i++) {
        *(p+i) = i * i + i;
    }
}

void printArr(int* p, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d \t", *p);
        p++;
    }
    printf("\n");
}