#include <stdio.h>
#include <errno.h>
#include <string.h>

/**

2 
No such file or directory 
fopen :: No such file or directory

 */
int main(void)
{
    FILE *fp = fopen("xxx.x", "r");

    if (NULL == fp)
    {
        printf("%d \n", errno);
        printf("%s \n", strerror(errno));

        perror("fopen :");
        return 1;
    }

    if (NULL != fp)
    {
        fclose(fp);
    }
    return 0;
}