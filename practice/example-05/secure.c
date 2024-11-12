#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

#include "secure.h"

#include <string.h>
#include <time.h>

void codeFile(const char *srcPath, const char *dest) {
    FILE* srcFile = fopen(srcPath, "rb");
    if (NULL == srcFile) {
        perror("fopen :");
        return;
    }
    FILE* desFile = fopen(srcPath, "wb+");
    srand(time(NULL));
    while(!feof(srcFile)) {
        short c = (short) fgetc(srcFile);
        c = c << 4;
        c = c | 0x8000;
        c = c + rand() % 0x10;
        fprintf(desFile, "%hd", c);
    }
    fclose(srcFile);
    fclose(desFile);
    srcFile = NULL;
    desFile = NULL;
}

void decodeFile(const char *srcPath, const char *dest) {
    FILE* srcFile = fopen(srcPath, "rb");
    if (NULL == srcFile) {
        perror("fopen :");
        return;
    }
    FILE* desFile = fopen(dest, "wb+");
    short c = 0;
    while(!feof(srcFile)) {
        fscanf(srcFile, "%hd", &c);
        c <<= 1;
        c >>= 5;
        fputc((char) c, desFile);
    }
    fclose(srcFile);
    fclose(desFile);
    srcFile = NULL;
    desFile = NULL;
}
