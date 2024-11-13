#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "array_list.h"

extern void help();

extern void *create(InitList, void *);

extern void version(ListLength, ListEmpty, void *);

extern void insertOne(ListInsert, void *);

extern void destroyList(DestroyList, void *);


int main(int argc, char **argv) {
    char cmd;
    void *list = NULL;
    while (1) {
        printf("input cmd to test dynamic array: ");
        // 由于scanf一次输入 char/n 等内容，所以 在%前加一个空格可以隔离开
        scanf(" %c", &cmd);
        switch (cmd) {
            case 'q':
                destroyList(destroy, list);
                list = NULL;
                printf("byb ! \n");
                return EXIT_FAILURE;
            case 'c':
                list = create(initList, list);
                break;
            case 'i':
                insertOne(insert, list);
                break;
            case 'v':
                version(length, isEmpty, list);
                break;
            default:
                help();
        }
    }

    return EXIT_SUCCESS;
}

void help() {
    printf("Cmds: \n");
    printf("\tc - create list\n");
    printf("\tq - quit\n");
}

void *create(const InitList func, void *list) {
    list = func(list, 10);
    return list;
}

void version(const ListLength sizeFunc, const ListEmpty emptyFunc, void *list) {
    const long size = sizeFunc(list);
    printf("size is %ld \n", size);
    printf("array is %s \n", emptyFunc(list) ? "empty" : "not empty");
}

void insertOne(const ListInsert func, void *list) {
    printf("which data you want to insert: ");
    int num, idx;
    scanf("%d", &num);
    printf("where you want to insert: ");
    scanf("%d", &idx);
    const int ret = func(list, idx, &num);
    if (-1 == ret) {
        printf("Error inserting element %d \n", num);
    } else {
        printf("inserting success element %d in %d \n", num, ret);
    }
}

void destroyList(const DestroyList func, void *list) {
    const int ret = func(list);
    if (1 != ret) {
        printf("Error in destroying element \n");
    }
    free(list);
}