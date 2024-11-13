#include <stdlib.h>
#include <stdio.h>

#include "array_list.h"


void* initList(void* array, int capacity) {
    Array *ptr = malloc(sizeof(Array));
    if (0 == ptr) {
        perror("malloc :");
        return NULL;
    }
    if (0 <= capacity) {
        capacity = 1;
    }
    ptr->data = calloc(capacity, sizeof(void*));
    ptr->size = 0;
    ptr->capacity = capacity;
    array = ptr;
    return ptr;
}

int isEmpty(Array array) {
    return 1;
}

int clean(Array* array) {
    return 0;
}

void* getElem(Array* array, int idx, void* elem) {
    return NULL;
}

int locate(Array* array, void* elem) {
    return -1;
}

int insert(Array* array, int idx, void* elem) {
    return -1;
}

void* delete(Array* array, int idx, void* elem) {
    return NULL;
}

long length(void* ptr) {
    if (NULL == ptr) {
        printf("ARRAY IS NULL! \n");
        return -1L;
    }
    return ((Array*)ptr)->size;
}

int destroy(Array* array) {
    return 0;
}
