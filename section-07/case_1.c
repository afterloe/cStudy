#include <stdlib.h>
#include <stdio.h>

void testByC(const char *filepath)
{
    int i = 0;
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if (NULL == fp)
    {
        perror("fopen filed.");
    }
    while (1)
    {
        if ( (i = fgetc(fp)) == EOF)
        {
            break;
        }
        printf("%c", i);
    }

    fclose(fp);
}

int main(int argc, char **argv)
{
    char filepath[128] = "../LICENSE";
    testByC(filepath);
    return 0;
}