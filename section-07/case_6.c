#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stu
{
    char name[32];
    float source;
} Student;

int main(int argc, char **argv)
{
    FILE *fp = fopen("a.data", "r");
    if (NULL == fp)
    {
        perror("open :");
        return EXIT_FAILURE;
    }
    int size = 5;
    Student *ptr = calloc(size, sizeof(Student));
    memset(ptr, 0, size);
    fread(ptr, sizeof(Student), size, fp);

    for (int i = 0; i < size; i++) {
        printf("%s -> %.2f \n", (ptr+i)->name, (ptr+i)->source);
    }

    free(ptr);
    ptr = NULL;
    fclose(fp);
    return EXIT_SUCCESS;
}