#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include <string.h>

#define MAX_FILE_SIZE 1024
#define BUF_SIZE 1500

int main()
{
    int sfd, ret, max_idx, idx;
    sfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("SOCKET :");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 server;
    server.sin6_family = AF_INET6;
    server.sin6_port = htons(9300);
    server.sin6_addr = in6addr_any;

    ret = bind(sfd, (struct sockaddr *)&server, sizeof(server));
    if (ret == -1)
    {
        perror("bind :");
        exit(EXIT_FAILURE);
    }
    ret = listen(sfd, MAX_FILE_SIZE);
    if (ret == -1)
    {
        perror("listen :");
        exit(EXIT_FAILURE);
    }
    printf("INIT UDP SERVER SUCCESS \n");

    struct pollfd *list = calloc(MAX_FILE_SIZE, sizeof(struct pollfd)); // 申请数组
    char *chunk = calloc(BUF_SIZE, sizeof(char)); // 申请缓冲区
    for(int i = 0; i < MAX_FILE_SIZE; i++)
    {
        // 初始化
        (list + i)->fd = -1;
    }

    list->fd = sfd; // 将首地址设置为 socket
    list->events = POLLIN; // 设置首地址的 监听事件为 POLLIN
    max_idx = 0; // 初始化最大地址

    for (;;)
    {
        ret = poll(list, max_idx + 1, -1); // POLL
        if (list->revents & POLLIN) // 如果 事件是 POLLIN
        {
            // 客户端 accept
            struct sockaddr_in6 cli;
            socklen_t len = sizeof(cli);
            int clifd = accept(sfd, (struct sockaddr*)&cli, &len);
            char ip[32] = {0};
            inet_ntop(AF_INET6, &cli.sin6_addr, ip, sizeof(ip));
            printf("CLIENT[%s]:%d ACCEPT. \n", ip, ntohs(cli.sin6_port));

            // 将客户端的 socket 文件放入 list中
            for (idx = 0; idx < MAX_FILE_SIZE; idx++)
            {
                if ((list + idx)->fd < 0)
                {
                    (list+idx)->fd = clifd;
                    break;
                }
            }

            if (idx == MAX_FILE_SIZE)
            {
                printf("too many clients");
            }

            // 设置 新增的socket文件的 监听事件为 POLLIN
            (list+idx)->events = POLLIN;
            if (idx > max_idx)
            {
                max_idx = idx;
            }
            if (--ret == 0)
            {
                // 去除首地址 的变动为0 则继续监听
                continue;
            }
        }

        for (idx = 1; idx <= max_idx; idx++)
        {
            // 循环整个list
            if ((list + idx)->revents & POLLIN)
            {
                // 事件存在
                memset(chunk, 0, BUF_SIZE);
                int num = read((list + idx)->fd, chunk, MAX_FILE_SIZE);
                if (num == 0)
                {
                    printf("client close \n");
                    close((list+idx)->fd);
                    (list+idx)->fd = -1;
                }
                else 
                {
                    write(STDOUT_FILENO, chunk, num);
                    write((list + idx)->fd, chunk, num);
                }
            }
        }
    }

    free(chunk);
    chunk = NULL;
    free(list);
    list = NULL;
    close(sfd);

    return EXIT_SUCCESS;
}