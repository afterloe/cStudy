#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    char filepath[16] = "./a.txt";
    int fp = open(filepath, O_WRONLY | O_CREAT, 0600);
    if (-1 == fp) {
        perror("CREATE FIEL :");
        return EXIT_FAILURE;
    }
    char content[128] = "this is generator by c.";
    write(fp, content, strlen(content));
    printf("generator %s success. \n", filepath);
    int fc = close(fp);
    if (-1 == fc) {
        perror("CLOSE FILE :");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}