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

int isEmpty(const void* array) {
    const Array* ptr = array;
    if (ptr == NULL) {
        printf("array is empty\n");
        return -1;
    }
    if (ptr->size == 0) {
        return 1;
    }
    return 0;
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

int insert(void* array, int idx, void* elem) {
    Array* ptr = array;
    if (ptr == NULL) {
        printf("array is empty\n");
        return -1;
    }
    // 判断位置是否正确, 不正确则进行尾插入
    if (idx < 0 || idx > ptr->size) {
        idx = ptr->size;
    }

    // 判断容量是否足够， 不足自动扩容
    if (ptr->size >= ptr->capacity) {
        const int capacity = ptr->capacity * 2; // 每次翻倍
        void **newData = realloc(ptr->data, capacity * sizeof(void*));
        if (NULL == newData) {
            perror("realloc :");
            return -1;
        }
        ptr->data = newData;
        ptr->capacity = capacity;
    }

    for(int i = ptr->size - 1; i >= idx; i--)
    {
        ptr->data[i + 1] = ptr->data[i];
    }
    ptr->data[idx] = elem;
    ptr->size++;

    return idx;
}

void* delete(Array* array, int idx, void* elem) {
    return NULL;
}

long length(void* array) {
    if (NULL == array) {
        printf("ARRAY IS NULL! \n");
        return -1L;
    }
    return ((Array*)array)->size;
}

int destroy(Array* array) {
    return 0;
}
