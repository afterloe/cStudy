#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>


int main()
{
    int cs, ret;
    cs = socket(AF_INET6, SOCK_DGRAM, 0);
    if (cs == -1)
    {
        perror("socket :");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 addr;
    addr.sin6_addr = in6addr_any;
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(9620);
    char chunk[1500] = {0};
    while(fgets(chunk, 1500, stdin) != NULL)
    {
        ret = sendto(cs, chunk, strlen(chunk), 0, (struct sockaddr *)&addr, sizeof(addr));
        if (ret == -1)
        {
            perror("sendto :");
        }
        memset(chunk, 0, 1500);
        ret = recvfrom(cs, chunk, 1500, 0, NULL, 0);
        if (ret == -1)
        {
            perror("recvfrom :");
        }
        write(STDOUT_FILENO, chunk, ret);
    }

    close(cs);
    return EXIT_SUCCESS;
}