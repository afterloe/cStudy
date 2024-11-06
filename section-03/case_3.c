#include <stdio.h>
#include <stdlib.h>

void printArr(int* ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d \t", *ptr);
        ptr++;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    printf("input you want size!\n");
    int size;
    scanf("%d", &size);
    int* ptr = (int*)malloc(size * sizeof(int));
    if (ptr == NULL) {
        perror("mallac failed");
    }
    printf("input %d nums\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", ptr+i);
    }
    printf("you input value \n");
    printArr(ptr, size);
    free(ptr);
    return 0;
}
