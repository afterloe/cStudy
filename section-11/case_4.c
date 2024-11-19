/**
 * ipv6 客户端
 */
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
    int ret;
    int sfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket :");
        return EXIT_FAILURE;
    }
    struct sockaddr_in6 servadd;
    servadd.sin6_family = AF_INET6;
    servadd.sin6_port = htons(9200);
    servadd.sin6_addr = in6addr_any; // 默认本地回环 ::1

    // 若指定ip地址， 需要进行 大小段地址转换

    // char ip[64] = "fe80::9c52:5446:eca6:abba";
    // const char* addr = (const char*)&servadd.sin6_addr.s6_addr;
    // inet_pton(AF_INET6, addr, ip);

    // 1.使用IPv6 链路本地地址， 需要设置sin6_scope_id，才能成功通信。
    // 2.IPv6 全局地址，不需要设置sin6_scope_id，就可以成功通信。
    // servadd.sin6_scope_id = 0x20;

    ret = connect(sfd, (struct sockaddr*)&servadd, sizeof(servadd));
    if (ret == -1)
    {
        perror("connect :");
        return EXIT_FAILURE;
    }

    char chunk[1500] = {0};

    while(1)
    {
        printf("input data you want to send. \n");
        int n = read(STDIN_FILENO, chunk, sizeof(chunk));
        write(sfd, chunk, n);
        memset(chunk, 0, sizeof(chunk));
        n = read(sfd, chunk, sizeof(chunk));
        if (0 == n)
        {
            break;
        }
        write(STDIN_FILENO, chunk, n);
    }

    printf("socket is end \n");

    close(sfd);
    return EXIT_SUCCESS;
}
