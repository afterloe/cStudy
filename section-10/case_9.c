#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

// 回调函数
void *thread_fun(void * arg)
{
    sleep(1);
    int num = *((int *)arg);
    printf("int the new thread: num = %d\n", num);

    return NULL;
}

int main()
{
    pthread_t tid;
    int test = 100;

    // 返回错误号
    int ret = pthread_create(&tid, NULL, thread_fun, (void *)&test);
    if (ret != 0)
    {
        printf("error number: %d\n", ret);
        // 根据错误号打印错误信息
        printf("error information: %d\n", strerror(ret));
    }

    while (1);

    return 0;
}