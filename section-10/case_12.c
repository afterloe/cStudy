#define SIZE 0x100000
​
void *th_fun(void *arg)
{
    while (1)
    {
        sleep(1);
    }
}
​
int main()
{
    pthread_t tid;
    int err, detachstate, i = 1;
​
    pthread_attr_t attr;
    size_t stacksize;
    void *stackaddr;
​
    pthread_attr_init(&attr);  //线程属性初始化
    pthread_attr_getstack(&attr, &stackaddr, &stacksize); //获取线程的栈地址
    pthread_attr_getdetachstate(&attr, &detachstate);           //获取线程分离状态
​
    if (detachstate == PTHREAD_CREATE_DETACHED)
    {
        printf("thread detached\n");
    }
    else if (detachstate == PTHREAD_CREATE_JOINABLE)
    {
        printf("thread join\n");
    }
    else
    {
        printf("thread unknown\n");
    }
        
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //设置分离状态
​
    while (1) 
    {
        stackaddr = malloc(SIZE);
        if (stackaddr == NULL) 
        {
            perror("malloc");
            exit(1);
        }
​
        stacksize = SIZE;
        pthread_attr_setstack(&attr, stackaddr, stacksize); //设置线程的栈地址
        err = pthread_create(&tid, &attr, th_fun, NULL); //创建线程
        if (err != 0) 
        {
            printf("%s\n", strerror(err));
            exit(1);
        }
        printf("%d\n", i++);
    }
​
    pthread_attr_destroy(&attr); //销毁线程属性所占用的资源函数
​
    return 0;
}