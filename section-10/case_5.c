#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd_pipe[2] = {0}; // 初始化管道, 0读 1写
    pid_t pid;
    int ret = pipe(fd_pipe);
    if (ret < 0)
    {
        perror("pipe :");
        _exit(-1);
    }

    pid = fork();
    if (0 == pid)
    {
        // 子进程 写数据
        char buf[] = "hello ubuntu";
        write(fd_pipe[1], buf, strlen(buf));
        _exit(0);
    }
    else if (pid > 0)
    {
        // 父进程 读数据

        // 设置读管道非阻塞
        int flags = fcntl(fd_pipe[0], F_GETFL); // 获取flag
        flags |= O_NONBLOCK; // 设置非阻塞
        fcntl(fd_pipe[0], F_SETFL, flags); // 设置回去

        wait(NULL);
        char content[50] = {0};
        // 如果写端没有关闭，读端设置为非阻塞， 如果没有数据，直接返回-1。
        read(fd_pipe[0], content, sizeof(content));
        printf("read content ===>  %s \n", content);
    }

    return 0;
} 