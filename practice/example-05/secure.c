#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

#include "secure.h"

#include <string.h>
#include <time.h>

void decode_file(const char* srcPath, const char* de) {
    srand(time(NULL));
    FILE* src = fopen(filepath, "r");
    if (src == NULL) {
        perror("open");
        return;
    }
    FILE* dst = fopen("b.cfg", "w");


    fclose(src);
    fclose(dst);
}
