#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1500

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("error to cat.");
        return EXIT_FAILURE;
    }
    argv++;
    FILE *fp = fopen(*argv, "r");
    if (NULL == fp)
    {
        perror("fopen :");
        return EXIT_FAILURE;
    }

    char *buf = calloc(BUFF_SIZE, sizeof(char));
    memset(buf, 0, BUFF_SIZE);

    while (
        fgets(buf, BUFF_SIZE, fp) != NULL)
    {
        fputs(buf, stdout);
    }

    free(buf);
    fclose(fp);
    return EXIT_SUCCESS;
}