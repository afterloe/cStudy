#include <string.h>
#include <stdio.h>

void strtokTest()
{
    char buf[] = "hehehe:hahaha:nonono:joe";
    char *arr[32] = {NULL};
    int i = 0;
    arr[i] = strtok(buf, ":");
    while (*(arr + i) != NULL)
    {
        i++;
        *(arr + i) = strtok(NULL, ":");
    }
    for (int idx = 0; idx < i; idx++)
    {
        printf("%s \n", arr[idx]);
    }
}

void strFormat()
{
    int year = 2024;
    int mon = 11;
    int day = 6;
    int len = 0;
    char buf[128] = "";
    len = sprintf(buf, "%d年%02d月%02d日", year, mon, day);
    printf("len = %d \n", len);
    printf("buf = %s \n", buf);
}

void strScanf() 
{
    char buf[] = "2024年11月06日";
    int year, mon, day;
    sscanf(buf, "%d年%02d月%02d日", &year, &mon, &day);
    printf("year = %d \n", year);
    printf("mon = %d \n", mon);
    printf("day = %d \n", day);
}

int main(int argc, char **argv)
{
    strtokTest();
    strFormat();
    strScanf();
    return 0;
}