#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define FILE_NAME_SIZE 256

typedef void CALLBACK(char*);

typedef struct linkedNode
{
    char* data;
    struct linkedNode* next;
} LinkedNode;

typedef struct linkedArray
{
    size_t size;
    LinkedNode* head;
} LinkeArray;

void appendItem(LinkeArray* arr, char* that)
{
    LinkedNode* node = malloc(sizeof(LinkedNode));
    node->data = calloc(strlen(that), sizeof(that));
    memcpy(node->data, that, strlen(that));
    node->next = NULL;

    if (arr->size == 0)
    {
        arr->head = node;
        arr->size = 1;
        return;
    }

    LinkedNode* ptr = arr->head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = node;
    arr->size += 1;
}

void iterator(LinkeArray* arr, CALLBACK callback)
{
    if (NULL == arr || arr->size == 0)
    {
        return;
    }
    LinkedNode* ptr = arr->head;
    while(ptr != NULL)
    {
        callback(ptr->data);
        ptr = ptr->next;
    }
}

void find_by_idx(LinkeArray* arr, int idx, CALLBACK callback)
{
    if (NULL == arr || arr->size == 0)
    {
        return;
    }
    if (idx > arr->size)
    {
        return;
    }
    int rt = 0;
    LinkedNode* ptr = arr->head;
    while(ptr != NULL)
    {
        if (rt == idx)
        {
            callback(ptr->data);
            break;
        }
        ptr = ptr->next;
        rt++;
    }
}

void loadMusic(LinkeArray* arr, char* dirname)
{
    char* ptr = NULL;
    DIR* dir = opendir(dirname);
    if (dir == NULL)
    {
        perror("opendir ");
        exit(1);
    }
    struct dirent* current = NULL;
    readdir(dir);

    while ((current = readdir(dir)) != NULL)
    {
        char* d_name = current->d_name;
        if (NULL == d_name)
        {
            continue;
        }
        if (!strcmp(".", d_name) || !strcmp("..", d_name))
        {
            continue;
        }
        if (strstr(d_name, ".flac") == NULL && strstr(d_name, ".mp3") == NULL)
        {
            continue;
        }

        char* filename = calloc(FILE_NAME_SIZE, sizeof(char));
        sprintf(filename, "%s/%s", dirname, d_name);
        if (current->d_type == DT_DIR)
        {
            loadMusic(arr, filename);
        }
        if (current->d_type == DT_REG)
        {
            appendItem(arr, filename);
        }
    }
    closedir(dir);
}


void print_value(char* filename)
{
    fprintf(stdout, "%s \n", filename);
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stdout, "Usage %s <dir> . \n", argv[0]);
    }
    // const char* input = argv[1];
    char* input = "/home/afterloe/音乐";
    LinkeArray* arr = NULL;
    arr = calloc(1, sizeof(LinkeArray));
    loadMusic(arr, input);
    fprintf(stdout, "find %ld \n", arr->size);
    // iterator(arr, print_value);
    find_by_idx(arr, 0, print_value);
    free(arr);
    return EXIT_SUCCESS;
}