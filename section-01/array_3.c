#include<stdio.h>

int main(int argc, char** argv) {
    int arr1[3][4] = {{1, 2}, {3}, {4}};
    int arr2[3][4] = {1, 2, 3, 4, 5};
    const int d = arr1[0][1] * arr2[1][0];
    printf("%d \n", d); // 2 * 5 = 10;
    return 0;
}
