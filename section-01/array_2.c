#include <stdio.h>

int main(int argc, char** argv) {
    int arr[6] = {10, 20, 30, 40, 50, 60};
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
        printf("%d \t", arr[i]);
    }
    printf("\n");

    return 0;
}
