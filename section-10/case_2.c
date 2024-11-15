#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int fd = open("case_1.c", O_RDONLY);
    int new_fd = fcntl(fd, F_DUPFD, 0); // 等价于 dup

    int flag = fcntl(fd, F_GETFL, 0);
    switch (flag & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only \n");
        break;
    case O_WRONLY:
        printf("write only \n");
        break;
    case O_RDWR:
        printf("read and write \n");
        break;
    default:
        break;
    }

    if (flag & O_APPEND)
    {
        printf("append \n");
    }

    return EXIT_SUCCESS;
}