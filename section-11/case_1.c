#include <stdio.h>

#include <arpa/inet.h>

int main()
{
    char ip[4] = {192, 168, 1, 1};
    int* ptr = (int *)ip;

    // 字节序转换 
    int sum = htonl(*ptr);
    unsigned char *cur = (unsigned char *) &sum;
    printf("[");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", *(cur+i));
    }
    printf("]\n");

    unsigned short a = 0x0102, b = htons(a);
    printf("sum = %x \n", b);
    return 0;
}