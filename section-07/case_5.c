#include <stdlib.h>
#include <stdio.h>

typedef struct stu
{
    char name[32];
    float source;
} Student;

int main(int argc, char **argv)
{
    Student students[] = {
        {"joe", 78},
        {"boo", 67},
        {"grace", 79},
        {"leo", 90},
        {"alis", 100}};

    FILE *p = fopen("a.data", "w");
    if (NULL == p)
    {
        perror("open:");
        return EXIT_FAILURE;
    }

    fwrite(students, sizeof(Student), sizeof(students) / sizeof(Student), p);
    fclose(p);
    return EXIT_SUCCESS;
}