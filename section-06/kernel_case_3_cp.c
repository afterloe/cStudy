#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("usage cp <src> <dest> \n");
        goto FINISH;
    }

    int ret = -1, src, dest;
    src = open(argv[1], O_RDONLY);
    if (src < 0)
    {
        perror("src :");
        goto FINISH;
    }
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (dest < 0)
    {
        perror("dest :");
        goto FINISH;
    }

    char* buff = calloc(BUFSIZ, sizeof(char));
    while ((ret = read(src, buff, BUFSIZ) != 0))
    {
        write(dest, buff, ret);
    }

FINISH:
    if (src > 0)
    {
        close(src);
    }
    if (dest > 0)
    {
        close(dest);
    }

    return EXIT_SUCCESS;
}