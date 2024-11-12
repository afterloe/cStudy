#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"

void help() {
    printf("Usage: ./app <filename>\n");
    printf("Example: *.dict.txt\n");
}


void free_dict(Dict **dict) {
    if (dict == NULL) {
        return;
    }
    Dict *current = *dict;
    Dict *next = NULL;
    while (current != NULL) {
        free(current->ch);
        free(current->en);
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
        if (0 == strcmp(word, current->en)) {
            printf("%s\n", current->ch);
            return;
        }
        if (NULL != strstr(current->ch, word)) {
            printf("%s\n", current->en);
            return;
        }
        current = current->next;
    }
    printf("can't find any about '%s' in dict. \n", word);
}

Dict *dict_new(Dict **head) {
    Dict *node = malloc(sizeof(Dict));
    if (node == NULL) {
        perror("malloc");
        return NULL;
    }
    node->next = NULL;

    Dict *node1 = malloc(sizeof(Dict));
    node1->en = calloc(128, sizeof(char));
    node1->ch = calloc(128, sizeof(char));
    strcpy(node1->en, "a");
    strcpy(node1->ch, "art. 一;字母A");

    Dict *node2 = malloc(sizeof(Dict));
    node2->en = calloc(128, sizeof(char));
    node2->ch = calloc(128, sizeof(char));
    strcpy(node2->en, "aback");
    strcpy(node2->ch, "向后地;朝后地");

    node = node1;
    node1->next = node2;
    node2->next = NULL;

    *head = node;
    return *head;
}
