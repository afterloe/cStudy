#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <string.h>

#define MAX_SIZE 1500

int main()
{
    int sfd, ret, num, idx, i;
    sfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("socket :");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 server;
    server.sin6_addr = in6addr_any;
    server.sin6_port = htons(9200);
    server.sin6_family = AF_INET6;

    ret = bind(sfd, (struct sockaddr*)&server, sizeof(server));
    if (-1 == ret)
    {
        perror("bind :");
        exit(EXIT_FAILURE);
    }
    ret = listen(sfd, MAX_SIZE);
    if (-1 == ret)
    {
        perror("listen :");
        exit(EXIT_FAILURE);
    }

    int handle = epoll_create(MAX_SIZE);
    struct epoll_event* list = calloc(MAX_SIZE, sizeof(struct epoll_event));
    memset(list, -1, MAX_SIZE);
    char* chunk = calloc(MAX_SIZE, sizeof(char));
    memset(chunk, 0, MAX_SIZE);

    list->data.fd = sfd;
    list->events = EPOLLIN;
    ret = epoll_ctl(handle, EPOLL_CTL_ADD, sfd, list);
    if (-1 == ret)
    {
        perror("epoll ctl :");
        exit(EXIT_FAILURE);
    }

    printf("WAIT TO ACCEPT \n");
    for (;;)
    {
        num = epoll_wait(handle, list, MAX_SIZE, -1);
        if (num == -1)
        {
            perror("wait :");
            break;
        }
        else if (num == 0)
        {
            continue;
        }
        else
        {
            for (idx = 0; idx < num; idx++)
            {
                if (!(list + idx)->events & EPOLLIN)
                {
                    continue;
                }
                if ((list + idx)->data.fd == sfd)
                {
                    struct sockaddr_in6 cli;
                    socklen_t len = sizeof(cli);
                    int cfd = accept((list + idx)->data.fd, (struct sockaddr*)&cli, &len);
                    if (cfd < 0)
                    {
                        perror("accept :");
                        continue;
                    }
                    
                    // 设置cfd 为非阻塞, 避免边缘触发时， read一直阻塞读取。
                    int model = fcntl(cfd, F_GETFL);
                    model |= O_NONBLOCK;
                    fcntl(cfd, F_SETFL, model);

                    char ip[32] = { 0 };
                    inet_ntop(AF_INET6, &cli.sin6_addr, ip, sizeof(ip));
                    printf("CLIENT[%s]:%d ACCEPT. \n", ip, ntohs(cli.sin6_port));

                    struct epoll_event node;
                    node.data.fd = cfd;
                    // 设置 epoll 为 边缘触发 模式， 即 只触发一次。
                    // 默认 水平触发， 即 只要有数据就一直循环
                    node.events = EPOLLIN | EPOLLET;
                    epoll_ctl(handle, EPOLL_CTL_ADD, cfd, &node);
                }
                else if ((list + idx)->events & EPOLLIN)
                {
                    // MSG_PEEK 表示读数据 不会删除缓冲区中的内容
                    int num = recv((list + idx)->data.fd, chunk, MAX_SIZE, MSG_CMSG_CLOEXEC);
                    if (num < 0)
                    {
                        CLOSE_CFD:
                        printf("close client \n");
                        epoll_ctl(handle, EPOLL_CTL_DEL, (list + idx)->data.fd, list);
                        close((list + idx)->data.fd);
                        break;
                    }
                    else if (num == 0)
                    {
                        goto CLOSE_CFD;
                    }
                    else
                    {
                        write(STDOUT_FILENO, chunk, num);
                        // send api, 0 表示一般速度， 1 表示紧急，一般设置0
                        send((list + idx)->data.fd, chunk, num, 0);
                    }
                }
            }
        }
    }

    free(list);
    list = NULL;
    free(chunk);
    chunk = NULL;

    close(sfd);
    return EXIT_SUCCESS;
}