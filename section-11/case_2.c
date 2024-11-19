#include <stdio.h>

#include <arpa/inet.h>

int main()
{
    int i;

    // 点分制 ip 地址转 32位 网络数据大端
    char ip[] = "192.168.1.1";
    unsigned int num = 0;
    inet_pton(AF_INET, ip, &num);
    unsigned char* p = (unsigned char *) &num;
    printf("\n[");
    for(i = 0; i < 4; i++)
    {
        printf("%d ", *(p+i));
    }
    printf("]\n");

    // 32位网络数据大段 转 点分制 ip地址
    char ipr[64] = {0};
    const char* cp = inet_ntop(AF_INET, &num, ipr, sizeof(ipr));
    printf("\n[");
    for (i = 0; *(cp+i) != 0; i++)
    {
        printf("%c ", *(cp+i));
    }
    printf("]\n");

    return 0;
}