
pthread_rwlock_t rwlock; //读写锁
int num = 1;
​
//读操作，其他线程允许读操作，却不允许写操作
void *fun1(void *arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("read num first===%d\n", num);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}
​
//读操作，其他线程允许读操作，却不允许写操作
void *fun2(void *arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("read num second===%d\n", num);
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
}
​
//写操作，其它线程都不允许读或写操作
void *fun3(void *arg)
{
    while (1)
    {
​
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("write thread first\n");
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
}
​
//写操作，其它线程都不允许读或写操作
void *fun4(void *arg)
{
    while (1)
    {
​
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("write thread second\n");
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}
​
int main()
{
    pthread_t ptd1, ptd2, ptd3, ptd4;
​
    pthread_rwlock_init(&rwlock, NULL);//初始化一个读写锁
​
    //创建线程
    pthread_create(&ptd1, NULL, fun1, NULL);
    pthread_create(&ptd2, NULL, fun2, NULL);
    pthread_create(&ptd3, NULL, fun3, NULL);
    pthread_create(&ptd4, NULL, fun4, NULL);
​
    //等待线程结束，回收其资源
    pthread_join(ptd1, NULL);
    pthread_join(ptd2, NULL);
    pthread_join(ptd3, NULL);
    pthread_join(ptd4, NULL);
​
    pthread_rwlock_destroy(&rwlock);//销毁读写锁
​
    return 0;
}