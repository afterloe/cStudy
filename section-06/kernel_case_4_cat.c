#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("usage cat <filename> \n");
        goto FINISH;
    }

    int ret = -1, fd;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open :");
        goto FINISH;
    }
    char *buff = NULL;
    buff = calloc(BUFSIZ, sizeof(char));
    while((ret = read(fd, buff, BUFSIZ)) != 0)
    {
        write(STDOUT_FILENO, buff, ret);
    }
    if (buff != NULL)
    {
        free(buff);
    }

FINISH:
    if (fd > 0)
    {
        close(0);
    }
    return EXIT_SUCCESS;
}