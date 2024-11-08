#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** args) {
    if (argc < 2) {
        printf("unknow src and dest, please invoke \n");
        return EXIT_FAILURE;
    }
    args++;
const    char * src = *args;
    args++;
    const char * dest = *args;

    printf("begint to copy %s to %s \n", src, dest);
    
    FILE *fs = fopen(src, "r");
    if (NULL == fs) {
        perror("SRC :");
        return EXIT_FAILURE;
    }
    FILE *fd = fopen(dest, "w+");
    if (NULL == fd) {
        perror("DEST :");
        return EXIT_FAILURE;
    }

    int rt, byte = 0;
    while((rt = fgetc(fs)) != EOF) {
        fputc(rt, fd);
        byte++;
    }

    printf("copy %d bytes. \n", byte);
    fclose(fs);
    fclose(fd);

    return EXIT_SUCCESS;
}