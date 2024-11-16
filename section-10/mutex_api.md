互斥锁 Mutex 
===

## 安装
```shell
sudo apt-get install manpages-posix-dev

man -k manpages-posix-dev
```

## 常用API

### int pthread_mutex_destroy(pthread_mutex_t *mutex)
头文件： #include <pthread.h>  
功能：
    销毁指定的一个互斥锁。互斥锁在使用完毕后，必须要对互斥锁进行销毁，以释放资源。   
参数：  
    mutex：互斥锁地址。   
返回值：  
    成功：0  
    失败：非 0 错误码  


### int pthread_mutex_lock(pthread_mutex_t *mutex)
头文件： #include <pthread.h>  
功能：
    对互斥锁上锁，若互斥锁已经上锁，则调用者阻塞，直到互斥锁解锁后再上锁。   
参数：   
    mutex：互斥锁地址。   
返回值：   
    成功：0   
    失败：非 0 错误码   

​
### int pthread_mutex_trylock(pthread_mutex_t *mutex)
头文件： #include <pthread.h>  
功能：
    对互斥锁上锁，若互斥锁已经上锁，则调用者阻塞，直到互斥锁解锁后再上锁。   
参数：   
    mutex：互斥锁地址。   
返回值：  
调用该函数时，若互斥锁未加锁，则上锁，返回 0；   
若互斥锁已加锁，则函数直接返回失败，即 EBUSY。
​

### int pthread_mutex_unlock(pthread_mutex_t *mutex)
头文件： #include <pthread.h>  
功能：  
    对指定的互斥锁解锁。   
参数：   
    mutex：互斥锁地址。   
返回值：  
    成功：0  
    失败：非0错误码  
​
> 相关测试代码[case_13.c](case_13.c)


### int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr)
头文件： #include <pthread.h>  
功能：
    用来初始化 rwlock 所指向的读写锁。  
​
参数：   
    rwlock：指向要初始化的读写锁指针。   
    attr：读写锁的属性指针。如果 attr 为 NULL 则会使用默认的属性初始化读写锁，否则使用指定的 attr 初始化读写锁。   
​
    可以使用宏 PTHREAD_RWLOCK_INITIALIZER 静态初始化读写锁，比如：
    pthread_rwlock_t my_rwlock = PTHREAD_RWLOCK_INITIALIZER;   
​
    这种方法等价于使用 NULL 指定的 attr 参数调用     pthread_rwlock_init() 来完成动态初始化，不同之处在于   PTHREAD_RWLOCK_INITIALIZER 宏不进行错误检查。   
​
返回值：   
    成功：0，读写锁的状态将成为已初始化和已解锁。   
    失败：非 0 错误码。  


### int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：  
    用于销毁一个读写锁，并释放所有相关联的资源（所谓的所有指的是由 pthread_rwlock_init() 自动申请的资源） 。    
参数：   
    rwlock：读写锁指针。   
返回值：   
    成功：0   
    失败：非 0 错误码   


### int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：   
    以阻塞方式在读写锁上获取读锁（读锁定）。   
    如果没有写者持有该锁，并且没有写者阻塞在该锁上，则调用线程会获取读锁。   
    如果调用线程未获取读锁，则它将阻塞直到它获取了该锁。一个线程可以在一个读写锁上多次执行读锁定。   
    线程可以成功调用 pthread_rwlock_rdlock() 函数 n 次，但是之后该线程必须调用 pthread_rwlock_unlock() 函数 n 次才能解除锁定。   
参数：   
    rwlock：读写锁指针。   
返回值：   
    成功：0   
    失败：非 0 错误码   
​

### int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：  
    用于尝试以非阻塞的方式来在读写锁上获取读锁。   
    如果有任何的写者持有该锁或有写者阻塞在该读写锁上，则立即失败返回。
​​参数：   
    rwlock：读写锁指针。   
返回值：   
    成功：0   
    失败：非 0 错误码   


### int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：   
    在读写锁上获取写锁（写锁定）。   
    如果没有写者持有该锁，并且没有写者读者持有该锁，则调用线程会获取写锁。   
    如果调用线程未获取写锁，则它将阻塞直到它获取了该锁。   
参数：   
    rwlock：读写锁指针。   
返回值：  
    成功：0  
    失败：非 0 错误码   
​

### int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：   
    用于尝试以非阻塞的方式来在读写锁上获取写锁。   
    如果有任何的读者或写者持有该锁，则立即失败返回。  
参数：   
    rwlock：读写锁指针。   
返回值：  
    成功：0  
    失败：非 0 错误码   


### int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
头文件： #include <pthread.h>  
功能：    
    无论是读锁或写锁，都可以通过此函数解锁。   
参数：   
    rwlock：读写锁指针。   
返回值：   
    成功：0   
    失败：非 0 错误码   

> 示例代码[case_14.c](case_14.c)


### int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
头文件： #include <pthread.h>  
功能：  
    初始化一个条件变量   
参数：   
    cond：指向要初始化的条件变量指针。   
    attr：条件变量属性，通常为默认值，传NULL即可   
        也可以使用静态初始化的方法，初始化条件变量：   
        pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   
返回值：   
    成功：0   
    失败：非0错误号   
​

### int pthread_cond_destroy(pthread_cond_t *cond)
头文件： #include <pthread.h>  
功能：    
    销毁一个条件变量   
参数：   
    cond：指向要初始化的条件变量指针   
返回值：   
    成功：0   
    失败：非0错误号   


### int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)
头文件： #include <pthread.h>  
功能：   
    阻塞等待一个条件变量   
    a) 阻塞等待条件变量cond（参1）满足   
    b) 释放已掌握的互斥锁（解锁互斥量）相当于pthread_mutex_unlock(&mutex);   
            a) b) 两步为一个原子操作。   
    c) 当被唤醒，pthread_cond_wait函数返回时，解除阻塞并重新申请获取互斥锁pthread_mutex_lock(&mutex);   
​
参数：  
    cond：指向要初始化的条件变量指针  
    mutex：互斥锁  
​
返回值：   
    成功：0   
    失败：非0错误号   
​

### int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct.*restrict abstime)
头文件： #include <pthread.h>  
功能：   
    限时等待一个条件变量   
参数：   
    cond：指向要初始化的条件变量指针   
    mutex：互斥锁    
    abstime：绝对时间   
返回值：   
    成功：0   
    失败：非0错误号   
​
abstime补充说明
```c
struct timespec {
    time_t tv_sec;      /* seconds */ // 秒
    long   tv_nsec; /* nanosecondes*/ // 纳秒
}
​
time_t cur = time(NULL);        //获取当前时间。
struct timespec t;              //定义timespec 结构体变量t
t.tv_sec = cur + 1;             // 定时1秒
pthread_cond_timedwait(&cond, &t);
```


### int pthread_cond_signal(pthread_cond_t *cond)
头文件： #include <pthread.h>  
功能：   
    唤醒至少一个阻塞在条件变量上的线程   
参数：   
    cond：指向要初始化的条件变量指针   
返回值：   
    成功：0   
    失败：非0错误号   
​

### int pthread_cond_broadcast(pthread_cond_t *cond)
头文件： #include <pthread.h>   
功能：   
    唤醒全部阻塞在条件变量上的线程   
参数：   
    cond：指向要初始化的条件变量指针   
返回值：   
    成功：0   
    失败：非0错误号    

> 示例代码[case_15.c](case_15.c)