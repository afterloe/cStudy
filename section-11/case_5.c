#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <sys/select.h>

#include <string.h>


int main(int argc, char** argv)
{
    int ss, port, ret;
    if (argc != 3)
    {
        printf("usage <SELECT> hostname port \n");
        return EXIT_FAILURE;
    }
    ss = socket(AF_INET6, SOCK_STREAM, 0);
    if (-1 == ss)
    {
        perror("socket :");
        exit(EXIT_FAILURE);
    }
    port = atoi(argv[2]);

    struct sockaddr_in6 addr;
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port);
    addr.sin6_addr = in6addr_any;

    // 设置端口复用
    int opt = 1;
    setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    ret = bind(ss, (struct sockaddr*)&addr, sizeof(addr));

    if (-1 == ret)
    {
        perror("bind :");
        exit(EXIT_FAILURE);
    }

    ret = listen(ss, 128);
    if (-1 == ret)
    {
        perror("listen :");
        exit(EXIT_FAILURE);
    }

    printf("SELECT SERVER SUCCESS INIT. \n");

    // 设置 SELECT
    // 设置最大文件是 socket文件
    int max_fd = ss;

    // 设置SELECT 队列为0
    fd_set oldset, rset;
    FD_ZERO(&oldset);
    FD_ZERO(&rset);

    // 将Socket 加入到oldset内
    FD_SET(ss, &oldset);

    while (1)
    {
        rset = oldset; // 将oldset 赋值给需要监听的rset中
        int n = select(max_fd + 1, &rset, NULL, NULL, NULL);
        if (n < 0)
        {
            perror("SELECT :");
            exit(EXIT_FAILURE);
        }
        else if (n = 0)
        {
            // 队列没有变化，即 没有客户端进行accept操作
            continue;
        }
        else
        {
            // 队列有变化
            if (FD_ISSET(ss, &rset)) // 检查 ss是否重新设置进了需要监听的队列中
            {
                // 获取客户端
                struct sockaddr_in6 client;
                socklen_t len = sizeof(client);
                int cs = accept(ss, (struct sockaddr*)&client, &len);
                if (-1 == cs)
                {
                    perror("accept :");
                    exit(EXIT_FAILURE);
                }

                char clientIP[32] = { 0 };
                inet_ntop(AF_INET6, &client.sin6_addr, clientIP, sizeof(clientIP));
                printf("CLIENT[%s]:%d ACCEPT. \n", clientIP, ntohs(client.sin6_port));

                FD_SET(cs, &oldset); // 将客户端放进oldset集合，下次监听
                // 更新maxfd
                if (cs > max_fd)
                {
                    max_fd = cs;
                }
                // 如果只有ss有变化，则跳出循环，继续等待客户端
                if (--n == 0)
                {
                    continue;
                }
            }

            // 遍历reset
            for (int i = ss + 1; i <= max_fd; i++)
            {
                if (FD_ISSET(i, &rset))
                {
                    char chunk[1500] = { 0 };
                    int ret = read(i, chunk, sizeof(chunk));
                    if (ret < 0)
                    {
                        printf("read socket \n");
                        close(i);
                        FD_CLR(i, &oldset);
                        continue;
                    }
                    if (ret == 0)
                    {
                        printf("socket is end \n");
                        close(i);
                        FD_CLR(i, &oldset);
                    }
                    else
                    {
                        write(STDOUT_FILENO, chunk, ret);
                        write(i, chunk, ret);
                    }
                }
            }
        }
    }

    close(ss);

    return EXIT_SUCCESS;
}