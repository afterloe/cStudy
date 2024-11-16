sem_t sem; //信号量
​
void printer(char *str)
{
    sem_wait(&sem);//减一
    while (*str)
    {
        putchar(*str);
        fflush(stdout);
        str++;
        sleep(1);
    }
    printf("\n");
​
    sem_post(&sem);//加一
}
​
void *thread_fun1(void *arg)
{
    char *str1 = "hello";
    printer(str1);
}
​
void *thread_fun2(void *arg)
{
    char *str2 = "world";
    printer(str2);
}
​
int main(void)
{
    pthread_t tid1, tid2;
​
    sem_init(&sem, 0, 1); //初始化信号量，初始值为 1
​
    //创建 2 个线程
    pthread_create(&tid1, NULL, thread_fun1, NULL);
    pthread_create(&tid2, NULL, thread_fun2, NULL);
​
    //等待线程结束，回收其资源
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
​
    sem_destroy(&sem); //销毁信号量
​
    return 0;
}