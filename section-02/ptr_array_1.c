#include <stdio.h>

int main(int argc, char** argv) {
    char *arr[3] = {"hello", "ubuntu", "!"};
    char** ptr = NULL;
    ptr = arr;
    for (int idx = 0; idx < sizeof(arr)/sizeof(arr[0]); idx++) {
        printf("%s \t", *ptr);
        ptr++;
    }
    printf("\n");
    return 0;
}
