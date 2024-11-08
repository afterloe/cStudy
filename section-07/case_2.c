#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char buf[1500] = {0};
    printf("input content which you want to write file. \n");
    // scanf("%s", buf);  // 使用该方法碰到空格键会中断
    fgets(buf, sizeof(buf), stdin);

    FILE *fp = fopen("./a.txt", "w+");
    if (NULL == fp) {
        perror("open file :");
        return EXIT_FAILURE;
    }

    int i = 0;
    while(buf[i] != '\0') {
        fputc(buf[i], fp);
        i++;
    }

    // int bytes = sizeof(buf) / sizeof(buf[0]);
    // for (int i = 0; i < bytes; i++) {
    //     fputc(buf[i], fp);
    // }

    printf("write %d to file -> a.txt done \n", i);
    fclose(fp);

    return EXIT_SUCCESS;
}