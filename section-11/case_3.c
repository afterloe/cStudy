/**
 * ip6 服务端
 */
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char** args)
{
    int ret;
    int sfd = socket(AF_INET6, SOCK_STREAM, 0); // 创建一个ipv6 的 数据读写socket， 协议使用默认
    if (sfd == -1)
    {
        perror("failed to open socket \n");
        return EXIT_FAILURE;
    }

    // 创建socket 服务 监听地址
    struct sockaddr_in6 servadd;
    servadd.sin6_family = AF_INET6;
    servadd.sin6_port = htons(9200);
    servadd.sin6_addr = in6addr_any;

    // 指定监听地址 需要进行大小端转换
    // char ip[32] = ":::";
    // const char* addr = (const char*)&servadd.sin6_addr.s6_addr;
    // inet_pton(AF_INET6, addr, ip);

    // 绑定
    ret = bind(sfd, (struct sockaddr*)&servadd, sizeof(servadd));
    if (ret == -1)
    {
        perror("bind :");
        return EXIT_FAILURE;
    }

    // 监听
    ret = listen(sfd, 128);
    if (ret == -1)
    {
        perror("listen :");
        return EXIT_FAILURE;
    }

    printf("socket server init.\n");
    printf("wait accept ! \n");

    struct sockaddr_in6 client;
    socklen_t len = sizeof(client);
    int cfd = accept(sfd, (struct sockaddr*)&client, &len);
    if (cfd == -1)
    {
        perror("accepd :");
        return EXIT_FAILURE;
    }
    char client_ip[32] = { 0 };
    printf("accept ip: %s:%d \n", inet_ntop(AF_INET6, &client.sin6_addr.s6_addr, client_ip, sizeof(client_ip)), ntohs(client.sin6_port));

    char chunk[1500] = {0};
    while(1)
    {
        int n = read(cfd, chunk, sizeof(chunk));
        if (0 == n)
        {
            printf("socket is close \n");
            break;
        }
        write(STDOUT_FILENO, chunk, n);
        write(cfd, chunk, n);
    }

    close(cfd);
    close(sfd);

    return EXIT_SUCCESS;
}