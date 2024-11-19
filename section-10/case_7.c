#include <stdio.h>
#include <signal.h>

#include <stdlib.h>

int main()
{
    sigset_t set; // 定义一个信号集变量
    int ret = 0;
    ​sigemptyset(&set); // 清空信号集的内容
    ​
        // 判断 SIGINT 是否在信号集 set 里
        // 在返回 1， 不在返回 0
        ret = sigismember(&set, SIGINT);
    if (ret == 0)
    {
        printf("SIGINT is not a member of set \nret = %d\n", ret);
    }
    ​sigaddset(&set, SIGINT); // 把 SIGINT 添加到信号集 set
    sigaddset(&set, SIGQUIT);    // 把 SIGQUIT 添加到信号集 set
        // 判断 SIGINT 是否在信号集 set 里
        // 在返回 1， 不在返回 0
        ret = sigismember(&set, SIGINT);
    if (ret == 1)
    {
        printf("SIGINT is a member of set \nret = %d\n", ret);
    }
    ​ sigdelset(&set, SIGQUIT); // 把 SIGQUIT 从信号集 set 移除
    ​
        // 判断 SIGQUIT 是否在信号集 set 里
        // 在返回 1， 不在返回 0
        ret = sigismember(&set, SIGQUIT);
    if (ret == 0)
    {
        printf("SIGQUIT is not a member of set \nret = %d\n", ret);
    }

    return EXIT_SUCCESS;
}