#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "secure.h"

void help() {
    printf("Usage: secureView opt <src filename> <dest filename>\n");
    printf("Options: -c code -d decode\n");
    printf("\t<src filename> - Filename to read from\n");
    printf("\t<dest filename> - Filename to write into\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        help();
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "-c") == 0) {
        code_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "-d") == 0) {
        decode_file(argv[2], argv[3]);
    } else {
        help();
    }
    return EXIT_SUCCESS;
}