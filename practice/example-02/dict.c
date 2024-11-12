#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"

#define WORD_LEN  128
#define BUFF_SIZE 1500

void help() {
    printf("Usage: ./app <filename>\n");
    printf("Example: ./app *.dict.txt\n");
}


void free_dict(Dict **dict) {
    if (dict == NULL) {
        return;
    }
    Dict *current = *dict;
    Dict *next = NULL;
    while (current != NULL) {
        free(current->key);
        free(current->val);
        next = current->next;
        free(current);
        current = next;
    }
}

void find(const char *word, Dict *dict) {
    if (NULL == word || NULL == dict) {
        printf("input error\n");
        return;
    }
    Dict *current = dict;
    while (NULL != current) {
        if (0 == strcmp(word, current->key)) {
            printf("%s\n", current->val);
            return;
        }
        current = current->next;
    }
    printf("can't find any about '%s' in dict. \n", word);
}

Dict *load_dict_by_txt(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("can't open file %s\n", filepath);
        return NULL;
    }
    Dict *head = NULL;
    char *buf = calloc(BUFF_SIZE, sizeof(char));
    int item = 0;
    while (!feof(fp)) {
        Dict *node = malloc(sizeof(Dict));
        node->next = NULL;
        item++;
    LOAD:
        memset(buf, 0, BUFF_SIZE);
        fgets(buf, BUFF_SIZE, fp);
        if (strlen(buf) == 0) {
            continue;
        }
        sscanf(buf, "%[^\r\n]", buf);
        const size_t len = strlen(buf) + 1;
        if (strstr(buf, "#") != NULL) {
            node->key = calloc(len, sizeof(char));
            node->key = strcpy(node->key, buf + 1);
            goto LOAD;
        }
        if (strstr(buf, "Trans:") != NULL) {
            node->val = calloc(len, sizeof(char));
            node->val = strcpy(node->val, buf + 6);
        }
        head = add_dict(head, node);
    }

    free(fp);
    free(buf);
    printf("load %d item \n", item);
    return head;
}

Dict *add_dict(Dict *ptr, Dict *node) {
    if (NULL != ptr) {
        node->next = ptr;
    }
    ptr = node;
    return ptr;
}

Dict *dict_new(Dict **head, const char *filepath) {
    printf("loading dict... from %s \n", filepath);
    Dict *node = NULL;
    if (strstr(filepath, ".txt") != NULL) {
        // load txt
        node = load_dict_by_txt(filepath);
    } else if (strstr(filepath, ".csv") != NULL) {
        // load csv
    }

    *head = node;
    return *head;
}
