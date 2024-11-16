PV信号量相关API
===

## 重点API

### int sem_init(sem_t *sem, int pshared, unsigned int value)
头文件： #include <semaphore.h>   
功能：   
    创建一个信号量并初始化它的值。一个无名信号量在被使用前必须先初始化。   
参数：   
    sem：信号量的地址。   
    pshared：等于 0，信号量在线程间共享（常用）；不等于0，信号量在进程间共享。   
    value：信号量的初始值。   
返回值：   
    成功：0   
    失败： - 1   
​

### int sem_destroy(sem_t *sem)
头文件： #include <semaphore.h>   
功能：    
    删除 sem 标识的信号量。   
参数：   
    sem：信号量地址。   
返回值：   
    成功：0    
    失败： -1   


### int sem_wait(sem_t *sem)
头文件： #include <semaphore.h>   
功能：   
    将信号量的值减 1。操作前，先检查信号量（sem）的值是否为 0，若信号量为 0，此函数会阻塞，直到信号量大于 0 时才进行减 1 操作。   
参数：   
    sem：信号量的地址。   
返回值：   
    成功：0   
    失败： - 1   
​

### int sem_trywait(sem_t *sem)
头文件： #include <semaphore.h>   
功能：   
    将信号量的值减 1。以非阻塞的方式来对信号量进行减 1 操作。若操作前，信号量的值等于 0，则对信号量的操作失败，函数立即返回。
参数：   
    sem：信号量的地址。   
返回值：   
    成功：0   
    失败： - 1   

​
### int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
头文件： #include <semaphore.h>   
功能：   
    限时尝试将信号量的值减 1。
参数：   
    sem：信号量的地址。     
    abs_timeout：绝对时间
返回值：   
    成功：0   
    失败： -1    

abs_timeout 结构体如下
```c
struct timespec {
    time_t tv_sec;      /* seconds */ // 秒
    long   tv_nsec; /* nanosecondes*/ // 纳秒
}
​
time_t cur = time(NULL);        //获取当前时间。
struct timespec t;              //定义timespec 结构体变量t
t.tv_sec = cur + 1;             // 定时1秒
sem_timedwait(&cond, &t);
```


### int sem_post(sem_t *sem)
头文件： #include <semaphore.h>   
功能：   
    将信号量的值加 1 并发出信号唤醒等待线程（sem_wait()）。   
参数：   
    sem：信号量的地址。   
返回值：   
    成功：0   
    失败：-1   


### int sem_getvalue(sem_t *sem, int *sval)
头文件： #include <semaphore.h>   
​功能：   
    获取 sem 标识的信号量的值，保存在 sval 中。   
参数：   
    sem：信号量地址。   
    sval：保存信号量值的地址。   
返回值：   
    成功：0   
    失败：-1   

​
> 示例代码[case_16.c](case_16.c)