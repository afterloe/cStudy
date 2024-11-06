#include <stdio.h>

int strLen(char *p)
{
    int size = 0;
    do
    {
        size++;
    } while (*(p + size) != 0);
    return size;
}

int main(int argc, char **argv)
{
    char v[128] = {"hello world"};
    printf("%s \n", v);
    printf("%ld \n", sizeof(v) / sizeof(char));
    int size =  strLen(v);
    printf("%d \n", size);

    return 0;
}