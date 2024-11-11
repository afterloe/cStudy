#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "configModel.h"

#define BUF_SIZE 1500
#define STR_LEN 100

Config *readConfig(const char *filepath) {
    Config *head = NULL;
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if (NULL == fp) {
        perror("open file :");
        return NULL;
    }

    char *buf = calloc(BUF_SIZE, sizeof(char));
    while (!feof(fp)) {
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, fp);
        if (strchr(buf, '=') == NULL) {
            continue;
        }
        sscanf(buf, "%[^\n]", buf);
        const char *content = strtok(buf, "=");
        if (NULL == content) {
            continue;
        }
        Config *node = malloc(sizeof(Config));
        memset(node, 0, sizeof(Config));
        node->value = calloc(STR_LEN, sizeof(char));
        node->key = calloc(STR_LEN, sizeof(char));
        node->next = NULL;
        strcpy(node->key, content);
        content = strtok(NULL, buf);
        strcpy(node->value, content);
        head = add(head, node);
    }


    free(buf);
    buf = NULL;
    fclose(fp);
    fp = NULL;

    return head;
}

Config *add(Config *ptr, Config *node) {
    if (NULL != ptr) {
        node->next = ptr;
    }
    ptr = node;
    return ptr;
}

void printCfg(const Config *ptr) {
    if (NULL == ptr) {
        printf("Config is empty; \n");
        return;
    }
    while (ptr != NULL) {
        printf("%s -> %s \n", ptr->key, ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}
