#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "array_list.h"

extern void help();
extern void init(InitList, void*);
extern void version(ListLength, void*);


int main(int argc, char** argv) {
    char cmd;
    void* list = NULL;
    while (1)
    {
        printf("input cmd to test dynamic array: ");
        // 由于scanf一次输入 char/n 等内容，所以 在%前加一个空格可以隔离开
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'q':
            printf("byb ! \n");
            return EXIT_FAILURE;
        case 'i':
            init(initList, list);
            break;
        case 'v':
            version(length, list);
            break;
        default:
            help();
        }
    }

    return EXIT_SUCCESS;
}

void help() {
    printf("Cmds: \n");
    printf("\tq - quit\n");
}

void init(InitList func, void* list) {
    list = func(list, 10);
}

void version(ListLength func, void* list) {
    int size = func(list);
    printf("size is %d \n", size);
}