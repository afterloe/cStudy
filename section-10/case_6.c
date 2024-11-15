#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>  
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int fd = open("a.txt", O_RDWR); // 文件必须存在，且大小不为0, 否则会报 Invalid argument
    int len = lseek(fd, 0, SEEK_END); // 读取文件大小

    void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap error :");
        _exit(1);
    }
    close(fd);

    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(3);
        printf("%s \n", (char*)ptr);
    }
    else if (pid > 0)
    {
        strcpy((char*)ptr, "you fater write");
        wait(NULL);
    }

    int ret = munmap(ptr, len);
    if (ret == -1)
    {
        perror("munmap error :");
        _exit(1);
    }

    return 0;
}
