void *thead(void *arg)
{
    static int num = 123; //静态变量
​
    printf("after 2 seceonds, thread will return\n");
    sleep(2);
​
    return &num;
}
​
int main()
{
    pthread_t tid;
    int ret = 0;
    void *value = NULL;
​
    // 创建线程
    pthread_create(&tid, NULL, thead, NULL);
​
​
    // 等待线程号为 tid 的线程，如果此线程结束就回收其资源
    // &value保存线程退出的返回值
    pthread_join(tid, &value);
​
    printf("value = %d\n", *((int *)value));
​
    return 0;
}