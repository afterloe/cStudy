#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char filepath[128] = "../LICENSE";
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        perror("open ::");
    }
    char buf[1500] = {0};
    int ret = -1;
    while((ret = read(fd, buf, 1500)) != 0) {
        write(STDOUT_FILENO, buf, ret);
    }
    close(fd);
    return EXIT_SUCCESS;
}