void *thread(void *arg)
{
    static int num = 123; //静态变量
    int i = 0;
    while (1)
    {
        printf("I am runing\n");
        sleep(1);
        i++;
        if (i == 3)
        {
            pthread_exit((void *)&num);
            // return &num;
        }
    }
​
    return NULL;
}
​
int main(int argc, char *argv[])
{
    int ret = 0;
    pthread_t tid;
    void *value = NULL;
​
    pthread_create(&tid, NULL, thread, NULL);
​
​
    pthread_join(tid, &value);
    printf("value = %d\n", *(int *)value);
​
    return 0;
}
​