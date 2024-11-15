#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/*

fork() 之后的打印函数打印了两次，而且打印了两个进程号，这说明，fork() 之后确实创建了一个新的进程，新进程为子进程，原来的进程为父进程

*/
int main()
{
    pid_t fpid;
    fpid = fork(); // 创建进程
    printf("id ==== %d \n", getpid());
    printf("fork pid ==== %d \n", fpid);
    
    if (0 == fpid)
    {
        printf("son \n");
    }
    else if (fpid > 0)
    {
        printf("father \n");
    }

    return 0;
}