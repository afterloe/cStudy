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
    // servadd.sin6_addr = in6addr_any;

    char ip[16] = "::1";
    const char* addr = (const char*)&servadd.sin6_addr.s6_addr;
    inet_pton(AF_INET6, addr, ip);
    

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
