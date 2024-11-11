#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "decode.h"

void codeFile(const char* src, const char* des) {
    FILE* srcFile = fopen(src, "rb");
    if (NULL == srcFile) {
        perror("fopen :");
        return;
    }
    FILE* desFile = fopen(des, "wb+");
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


void encodeFile(const char* src, const char* des) {
    FILE* srcFile = fopen(src, "rb");
    if (NULL == srcFile) {
        perror("fopen :");
        return;
    }
    FILE* desFile = fopen(des, "wb+");
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