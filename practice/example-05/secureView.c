#include <stdio.h>
#include <stdlib.h>

#include "secure.h"

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     printf("Usage: secureView <filename>\n");
    //     return EXIT_FAILURE;
    // }
    // decode_file(argv[1]);
    decode_file("a.cfg");
    return EXIT_SUCCESS;
}