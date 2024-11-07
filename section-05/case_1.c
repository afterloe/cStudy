#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stu
{
    int sourcr;
    char name[10];
};

int main(int argc, char** argv) {
    struct stu* p = malloc(sizeof(struct stu));
    if (NULL == p) {
        perror("malloc failed");
    }
    
    memset(p, 0, sizeof(struct stu));
    printf("please input students name \n");
    scanf("%s", p->name);
    printf("please input %s 的分数： \n", p->name);
    scanf("%d", &(p->sourcr));
    char msg[128] = {};
    sprintf(msg, "%s的分数为%d", p->name, p->sourcr);
    printf("inputs: %s \n", msg);

    if (NULL != p) {
        free(p);
        p = NULL;
    }

    return 0;
}