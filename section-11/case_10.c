#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>

int main()
{
    int fd, len, ret;
    char filepath[32] = "/tmp/a.socket";
    struct sockaddr_un un;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("unix socket :");
        exit(EXIT_FAILURE);
    }

    unlink(filepath);
    
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, filepath);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(filepath);

    ret = bind(fd, (struct sockaddr *)&un, len);
    if (-1 == ret)
    {
        printf("bind :");
        exit(EXIT_FAILURE);
    }
    ret = listen(fd, 10);
    if (-1 == ret)
    {
        printf("listen :");
        exit(EXIT_FAILURE);
    }

    printf("uds ready.\n");
    
    struct sockaddr_un cli;
    socklen_t c_len = sizeof cli;
    int clifd = accept(fd, (struct sockaddr *)&cli, &c_len);
    if (clifd < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char chunk[1500] = {0};
    for (;;)
    {
        memset(chunk, 0, sizeof(chunk));
        int n = recv(clifd, chunk, sizeof(chunk), 0);
        if (n == 0)
        {
            printf("client close.\n");
            break;
        }
        write(STDOUT_FILENO, chunk, n);
        send(clifd, chunk, n, 0);
    }

    close(clifd);
    close(fd);

    return EXIT_SUCCESS;
}