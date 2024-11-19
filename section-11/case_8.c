#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int us, ret;
    us = socket(AF_INET6, SOCK_DGRAM, 0);
    if (us < 0)
    {
        perror("socket :");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 server;
    server.sin6_family = AF_INET6;
    server.sin6_port = htons(9620);
    server.sin6_addr = in6addr_any;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(us, (struct sockaddr *) &server, sizeof(server));
    if (ret < 0)
    {
        perror("bind :");
        exit(EXIT_FAILURE);
    }

    printf("wait to accepting \n");
    char *chunk = calloc(1500, sizeof(char));
    char ip[32] = {0};
    struct sockaddr_in6 cli;
    socklen_t len = sizeof(cli);
    for(;;)
    {
        memset(chunk, 0, 1500);
        memset(ip, 0, 32);
        ret = recvfrom(us, chunk, 1500, 0, (struct sockaddr *)&cli, &len);
        if (ret == -1)
        {
            perror("recvfrom :");
            continue;
        }

        printf("client[%s]:%d accept. ",
                inet_ntop(AF_INET6, &cli.sin6_addr, ip, 32),
                ntohs(cli.sin6_port));
        write(STDOUT_FILENO, chunk, ret);
        ret = sendto(us, chunk, ret, 0, (struct sockaddr *)&cli, sizeof(cli));
        if (ret == -1)
        {
            perror("send :");
        }
    }

    free(chunk);
    chunk = NULL;
    close(us);

    return EXIT_SUCCESS;
}