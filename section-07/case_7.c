#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("less one arg \n");
        return EXIT_FAILURE;
    }
    struct stat *s = calloc(1, sizeof(struct stat));
    argv++;
    if (-1 == stat(*argv, s)) {
        perror("file stat :");
        return EXIT_FAILURE;
    }

    printf("%s size is %ld, create at %ld \n", *argv, s->st_size, s->st_ctime);

    free(s);
    s = NULL;
    return EXIT_SUCCESS;
}