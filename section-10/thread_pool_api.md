进程池API
===

## 线程函数列表安装
```shell
sudo apt-get install manpages-posix-dev

man -k pthread
```
> 线程函数的程序在**pthread**库中，故链接时要加上参数 `-lpthread。`

## 常用API

### pthread_t pthread_self(void)
头文件： #include <pthread.h>  
功能：
    获取线程号。  
参数：  
    无    
返回值：
    调用线程的线程 ID 。  


### int pthread_equal(pthread_t t1, pthread_t t2)
头文件： #include <pthread.h>    
功能：
    判断线程号 t1 和 t2 是否相等。为了方便移植，尽量使用函数来比较线程 ID。    
参数：  
    t1，t2：待判断的线程号。    
返回值：
    相等：  非 0
    不相等：0


### int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg )
头文件： #include <pthread.h>    
功能：
    创建一个线程。   
参数：  
    thread：线程标识符地址。   
    attr：线程属性结构体地址，通常设置为 NULL。   
    start_routine：线程函数的入口地址。  
    arg：传给线程函数的参数。   
返回值：  
    成功：0  
    失败：非 0  

> 参考代码[case_9.c](case_9.c)


### int pthread_join(pthread_t thread, void **retval)
头文件： #include <pthread.h>    
功能：
    等待线程结束（此函数会阻塞），并回收线程资源，类似进程的 wait() 函数。如果线程已经结束，那么该函数会立即返回。  
参数：  
    thread：被等待的线程号。   
    retval：用来存储线程退出状态的指针的地址。  
返回值：  
    成功：0  
    失败：非 0   
​
> 参考代码[case_10.c](case_10.c)


### int pthread_detach(pthread_t thread)
头文件： #include <pthread.h>    
功能：
    使调用线程与当前进程分离，分离后不代表此线程不依赖与当前进程，线程分离的目的是将线程资源的回收工作交由系统自动来完成，也就是说当被分离的线程结束之后，系统会自动回收它的资源。所以，此函数不会阻塞。   
参数：  
    thread：线程号。  
返回值：  
    成功：0  
    失败：非0  

> 不能对一个已经处于detach状态的线程调用pthread_join，这样的调用将返回EINVAL错误。也就是说，如果已经对一个线程调用了pthread_detach就不能再调用pthread_join了


### void pthread_exit(void *retval)
头文件： #include <pthread.h>    
功能：
    退出调用线程。一个进程中的多个线程是共享该进程的数据段，因此，通常线程退出后所占用的资源并不会释放。  
参数：   
    retval：存储线程退出状态的指针。   
返回值：无    

> 在进程中我们可以调用exit函数或_exit函数来结束进程，在一个线程中我们可以通过以下三种在不终止整个进程的情况下停止它的控制流。
>
> * 线程从执行函数中返回。
> * 线程调用pthread_exit退出线程。
> * 线程可以被同一进程中的其它线程取消。

> 参考代码[case_11.c](case_11.c)


### int pthread_cancel(pthread_t thread)
头文件： #include <pthread.h>    
功能：杀死(取消)线程
参数：   
    thread : 目标线程ID。  
返回值：  
    成功：0  
    失败：出错编号   

线程的取消并不是实时的，而又一定的延时。需要等待线程到达某个取消点


### int pthread_attr_init(pthread_attr_t *attr)
头文件： #include <pthread.h>    
功能：
    初始化线程属性函数，注意：应先初始化线程属性，再pthread_create创建线程   
参数：   
    attr：线程属性结构体，定义如下   
返回值：   
    成功：0   
    失败：错误号   
​


### int pthread_attr_destroy(pthread_attr_t *attr)
头文件： #include <pthread.h>    
功能：
    销毁线程属性所占用的资源函数   
参数：   
    attr：线程属性结构体，定义如下   
返回值：  
    成功：0   
    失败：错误号   

pthread_attr_t 结构定义如下：
```c
typedef struct
{
    int             etachstate;     //线程的分离状态
    int             schedpolicy;    //线程调度策略
    struct sched_param  schedparam; //线程的调度参数
    int             inheritsched;   //线程的继承性
    int             scope;      //线程的作用域
    size_t          guardsize;  //线程栈末尾的警戒缓冲区大小
    int             stackaddr_set; //线程的栈设置
    void*           stackaddr;  //线程栈的位置
    size_t          stacksize;  //线程栈的大小
} pthread_attr_t;
```


### int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
头文件： #include <pthread.h>    
功能：设置线程分离状态   
参数：   
    attr：已初始化的线程属性   
    detachstate：    分离状态   
        PTHREAD_CREATE_DETACHED（分离线程）   
        PTHREAD_CREATE_JOINABLE（非分离线程）   
返回值：   
    成功：0   
    失败：非0  
​

### int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
头文件： #include <pthread.h>    
功能：获取线程分离状态   
参数：   
    attr：已初始化的线程属性   
    detachstate：    分离状态   
        PTHREAD_CREATE_DETACHED（分离线程）   
        PTHREAD _CREATE_JOINABLE（非分离线程）   
返回值：   
    成功：0   
    失败：非0   
​
> 线程的分离状态决定一个线程以什么样的方式来终止自己。

* 非分离状态：线程的默认属性是非分离状态，这种情况下，原有的线程等待创建的线程结束。只有当pthread_join()函数返回时，创建的线程才算终止，才能释放自己占用的系统资源。
* 分离状态：分离线程没有被其他的线程所等待，自己运行结束了，线程也就终止了，马上释放系统资源。应该根据自己的需要，选择适当的分离状态。


> ps: 如果设置一个线程为分离线程，而这个线程运行又非常快，它很可能在pthread_create函数返回之前就终止了，它终止以后就可能将线程号和系统资源移交给其他的线程使用，这样调用pthread_create的线程就得到了错误的线程号。   
> 要避免这种情况可以采取一定的同步措施，最简单的方法之一是可以在被创建的线程里调用pthread_cond_timedwait函数，让这个线程等待一会儿，留出足够的时间让函数pthread_create返回


### int pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr,  size_t stacksize)
头文件： #include <pthread.h>    
功能：设置线程的栈地址   
参数：  
    attr：指向一个线程属性的指针   
    stackaddr：内存首地址   
    stacksize：返回线程的堆栈大小   
返回值：  
    成功：0  
    失败：错误号  
​

### int pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr,  size_t *stacksize)
头文件： #include <pthread.h>    
功能：获取线程的栈地址   
参数：   
    attr：指向一个线程属性的指针   
    stackaddr：返回获取的栈地址  
    stacksize：返回获取的栈大小  
返回值：  
    成功：0   
    失败：错误号   

```
POSIX.1定义了两个常量来检测系统是否支持栈属性：

_POSIX_THREAD_ATTR_STACKADDR
_POSIX_THREAD_ATTR_STACKSIZE
也可以给sysconf函数传递来进行检测：

_SC_THREAD_ATTR_STACKADDR
_SC_THREAD_ATTR_STACKSIZE
当进程栈地址空间不够用时，指定新建线程使用由malloc分配的空间作为自己的栈空间
```


### int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
头文件： #include <pthread.h>    
功能：设置线程的栈大小   
参数：   
    attr：指向一个线程属性的指针   
    stacksize：线程的堆栈大小   
返回值：   
    成功：0   
    失败：错误号   
​

### int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize)
头文件： #include <pthread.h>    
功能：获取线程的栈大小   
参数：   
    attr：指向一个线程属性的指针  
    stacksize：返回线程的堆栈大小   
返回值：   
    成功：0   
    失败：错误号   


当系统中有很多线程时，可能需要减小每个线程栈的默认大小，防止进程的地址空间不够用,当线程调用的函数会分配很大的局部变量或者函数调用层次很深时，可能需要增大线程栈的默认大小。


## 综合参考程序
[线程池](case_12.c)