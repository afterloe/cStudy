#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "dict.h"

int main(const int argc, const char **argv) {
    if (argc != 2) {
        help();
        return EXIT_FAILURE;
    }
    Dict *head = NULL;
    dict_new(&head, argv[1]);
    if (head == NULL) {
        printf("init dict failed.");
        return EXIT_FAILURE;
    }
    char *content = calloc(128, sizeof(char));
    while (1) {
        memset(content, 0, 128);
        printf("input word [:q to quit]: ");
        scanf("%s", content);
        if (strcmp(content, ":q") == 0) {
            break;
        }
        find(content, head);
    }
    free(content);
    return EXIT_SUCCESS;
}