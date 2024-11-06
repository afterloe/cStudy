#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int *addr = NULL;
    addr = (int*)malloc(sizeof(int));
    memset(addr, 0, sizeof(int));
    *addr = 10087;
    printf("%d \n", *addr);
    free(addr);
    return 0;
}
