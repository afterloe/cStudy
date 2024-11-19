进程相关api
===


### pid_t getpid(void)
头文件:   
   #include <sys/types.h>   
   #include <unistd.h>    
功能：   
    获取本进程号（PID）  
参数：   
    无   
返回值：   
    本进程号   


### pid_t getppid(void)
头文件:   
   #include <sys/types.h>   
   #include <unistd.h>    
功能：    
    获取调用此函数的进程的父进程号（PPID）    
参数：   
    无   
返回值：   
    调用此函数的进程的父进程号（PPID）    


### pid_t getpgid(pid_t pid)
头文件:   
   #include <sys/types.h>   
   #include <unistd.h>    
功能：   
    获取进程组号（PGID）   
参数：   
    pid：进程号    
返回值：    
    参数为 0 时返回当前进程组号，否则返回参数指定的进程的进程组号     

> 参考代码[case_3.c](case_3.c)


### pid_t fork(void)
头文件:   
   #include <sys/types.h>   
   #include <unistd.h>   
功能：    
    用于从一个已存在的进程中创建一个新进程，新进程称为子进程，原进程称为父进程。可以通过返回的`pid_t`的值判断是子进程还是父进程（pid_t == 0 子进程， 》0 父进程）。    
参数：   
    无   
返回值：   
    成功：子进程中返回 0，父进程中返回子进程 ID。pid_t，为整型。    
    失败：返回-1。    
    失败的两个主要原因是：    
        1）当前的进程数已经达到了系统规定的上限，这时 errno 的值被设置为 EAGAIN。    
        2）系统内存不足，这时 errno 的值被设置为 ENOMEM。    
> 参考代码[case_4.c](case_4.c)


### void exit(int status)
头文件:    
   #include <stdlib.h>   
功能：   
    结束调用此函数的进程。   
参数：   
    status：返回给父进程的参数（低 8 位有效），至于这个参数是多少根据需要来填写。   
返回值：   
    无   


### void _exit(int status)
头文件:   
   #include <unistd.h>   
功能：   
    结束调用此函数的进程。   
参数：   
    status：返回给父进程的参数（低 8 位有效），至于这个参数是多少根据需要来填写。   
返回值：
    无   


### pid_t wait(int *status)
头文件:   
   #include <sys/types.h>    
   #include <sys/wait.h>   
功能：   
    等待任意一个子进程结束，如果任意一个子进程结束了，此函数会回收该子进程的资源。    
参数：    
    status : 进程退出时的状态信息。   
返回值：    
    成功：已经结束子进程的进程号
    失败： -1    


### pid_t waitpid(pid_t pid, int *status, int options)
头文件:   
   #include <sys/types.h>    
   #include <sys/wait.h>   
功能：   
    等待子进程终止，如果子进程终止了，此函数会回收子进程的资源。   
参数：   
    pid : 参数 pid 的值有以下几种类型：    
      pid > 0  等待进程 ID 等于 pid 的子进程。   
      pid = 0  等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid 不会等待它。   
      pid = -1 等待任一子进程，此时 waitpid 和 wait 作用一样。   
      pid < -1 等待指定进程组中的任何子进程，这个进程组的 ID 等于 pid 的绝对值。   
​
    status : 进程退出时的状态信息。和 wait() 用法一样。   
​
    options : options 提供了一些额外的选项来控制 waitpid()。    
            0：同 wait()，阻塞父进程，等待子进程退出。   
            WNOHANG：没有任何已经结束的子进程，则立即返回。   
            WUNTRACED：如果子进程暂停了则此函数马上返回，并且不予以理会子进程的结束状态。（由于涉及到一些跟踪调试方面的知识，加之极少用到）   
                 
返回值：    
    waitpid() 的返回值比 wait() 稍微复杂一些，一共有 3 种情况：   
        1) 当正常返回的时候，waitpid() 返回收集到的已经回收子进程的进程号；   
        2) 如果设置了选项 WNOHANG，而调用中 waitpid() 发现没有已退出的子进程可等待，则返回 0；   
        3) 如果调用中出错，则返回-1，这时 errno 会被设置成相应的值以指示错误所在，如：当 pid 所对应的子进程不存在，或此进程存在，但不是调用进程的子进程，waitpid() 就会出错返回，这时 errno 被设置为 ECHILD；    

调用 wait() 函数的进程会挂起（阻塞），直到它的一个子进程退出或收到一个不能被忽视的信号时才被唤醒。    

> 一次wait或waitpid调用只能清理一个子进程，清理多个子进程应使用循环

status 宏
| 值 | 描述 | 使用方式 |
| ---- | --- | ------ |
| WIFEXITED | 为非0 → 进程正常结束 | WEXITSTATUS(status) 如上宏为真，使用此宏 → 获取进程退出状态 (exit的参数)
| WIFSIGNALED | 为非0 → 进程异常终止 | WTERMSIG(status) 如上宏为真，使用此宏 → 取得使进程终止的那个信号的编号。
| WIFSTOPPED | 为非0 → 进程处于暂停状态 | WSTOPSIG(status) 如上宏为真，使用此宏 → 取得使进程暂停的那个信号的编号。
| WIFCONTINUED | 为真 → 进程暂停后已经继续运行 | 


### 调用其他命令
```c
#include <unistd.h>
extern char **environ;
​
int execl(const char *path, const char *arg, .../* (char  *) NULL */);
int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);
int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
​
int execve(const char *filename, char *const argv[], char *const envp[]);
```
其中只有 `execve()` 是真正意义上的系统调用，其它都是在此基础上经过包装的库函数。    

进程调用一种 exec 函数时，该进程完全由新程序替换，而新程序则从其 main 函数开始执行。因为调用 exec 并不创建新进程，所以前后的进程 ID并未改变，其他都已变化。    

exec 函数族的 6 个函数看起来似乎很复杂，但实际上无论是作用还是用法都非常相似，只有很微小的差别    
![alt text](pic/thread_execv_image.png)

补充说明：
| 参数 | 说明 |
| ----- | ----- |
| l(list) |	参数地址列表，以空指针结尾
| v(vector) |	存有各参数地址的指针数组的地址
| p(path) |	按 PATH 环境变量指定的目录搜索可执行文件
| e(environment) |	存有环境变量字符串地址的指针数组的地址

exec 函数族中的函数执行成功后不会返回，而且，exec 函数族下面的代码执行不到。只有调用失败了，它们才会返回 -1，失败后从原程序的调用点接着往下执行   


### int pipe(int pipefd[2])
头文件:   
   #include <unistd.h>    
功能：   
    创建无名管道。   
​
参数：   
    pipefd : 为 int 型数组的首地址，其存放了管道的文件描述符 pipefd[0]、pipefd[1]。   
    
    当一个管道建立时，它会创建两个文件描述符 fd[0] 和 fd[1]。其中 fd[0] 固定用于读管道，而 fd[1] 固定用于写管道。一般文件 I/O的函数都可以用来操作管道(lseek() 除外)。   
​
返回值：
    成功：0   
    失败：-1   

> 参考代码[case_5.c](case_5.c)


### long fpathconf(int fd, int name)
头文件:   
   #include <unistd.h>    
功能：     
    该函数可以通过name参数查看管道的不同的属性值    
参数：    
    fd：文件描述符    
    name：    
        _PC_PIPE_BUF，查看管道缓冲区大小    
        _PC_NAME_MAX，文件名字字节数的上限   
返回值：   
    成功：根据name返回的值的意义也不同。    
    失败： -1    
eg `long num = fpatchconf(fd[0], _PC_PIPE_BUF);`


### int mkfifo(const char *pathname, mode_t mode)
头文件:   
    #include <sys/types.h>    
    #include <sys/stat.h>   
功能：   
    命名管道的创建。   
参数：   
    pathname : 普通的路径名，也就是创建后 FIFO 的名字。   
    mode : 文件的权限，与打开普通文件的 open() 函数中的 mode 参数相同。(0666)   
返回值：   
    成功：0   状态码   
    失败：如果文件已经存在，则会出错且返回 -1。   


### void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
头文件：   
   #include <sys/mman.h>
功能:    
    一个文件或者其它对象映射进内存   
参数：    
    addr :  指定映射的起始地址, 通常设为NULL, 由系统指定    
    length：映射到内存的文件长度    
    prot：  映射区的保护方式, 最常用的 :   
        a) 读：PROT_READ   
        b) 写：PROT_WRITE   
        c) 读写：PROT_READ | PROT_WRITE   
    flags：  映射区的特性, 可以是   
        a) MAP_SHARED : 写入映射区的数据会复制回文件, 且允许其他映射该文件的进程共享, 文件必须存在，大小不为0。   
        b) MAP_PRIVATE : 对映射区的写入操作会产生一个映射区的复制(copy - on - write), 对此区域所做的修改不会写回原文件, 使用次方式文件不必存在。    
    fd：由open返回的文件描述符, 代表要映射的文件。    
    offset：以文件开始处的偏移量, 必须是4k的整数倍, 通常为0, 表示从文件头开始映射    
返回值：   
    成功：返回创建的映射区首地址   
    失败：MAP_FAILED宏   

> 如果 使用 mmap 映射文件，则文件必须存在，且大小不为0

关于mmap函数的使用总结：
* 第一个参数写成NULL
* 第二个参数要映射的文件大小 > 0
* 第三个参数：PROT_READ 、PROT_WRITE
* 第四个参数：MAP_SHARED 或者 MAP_PRIVATE
* 第五个参数：打开的文件对应的文件描述符
* 第六个参数：4k的整数倍，通常为0

### int munmap(void *addr, size_t length)
头文件：   
   #include <sys/mman.h>
功能:    
   释放内存映射区    
参数：    
    addr：使用mmap函数创建的映射区的首地址    
    length：映射区的大小    
返回值：   
    成功：0   
    失败：-1   


共享映射的方式操作文件、父子进程通信的demo, 参考这里[case_6.c](case_6.c)
> 注意： 若使用 MAP_SHARED 方式，则文件必须存在，且大小不为0, 否则会报 Invalid argument  


### void signal(int sig, void (*func)(int))
头文件：   
    #include <signal.h>   
功能：  
    接收到一个信号后 执行某个函数，即设置信号处理程序   

参数:    
    sig:  信号量   
    func: 函数指针，void func(int sign)    

sig参数表
| 宏 | 信号及说明 |
|--- | --------- |
| SIGABRT |	(Signal Abort) 程序异常终止。
| SIGFPE |	(Signal Floating-Point Exception) 算术运算出错，如除数为 0 或溢出（不一定是浮点运算）。
| SIGILL |	(Signal Illegal Instruction) 非法函数映象，如非法指令，通常是由于代码中的某个变体或者尝试执行数据导致的。
| SIGINT |	(Signal Interrupt) 中断信号，如 ctrl-C，通常由用户生成。
| SIGSEGV |	(Signal Segmentation Violation) 非法访问存储器，如访问不存在的内存单元。
| SIGTERM |	(Signal Terminate) 发送给本程序的终止请求信号。

func 不想实现也可以用默认的宏 `SIG_DFL - 默认的信号处理程序。 | SIG_IGN - 忽视信号`


### int kill(pid_t pid, int sig)
头文件：   
    #include <sys/types.h>    
    #include <signal.h>    
功能：   
    给指定进程发送指定信号(不一定杀死)    
​
参数：   
    pid : 取值有 4 种情况 :    
        pid > 0:  将信号传送给进程 ID 为pid的进程。   
        pid = 0 :  将信号传送给当前进程所在进程组中的所有进程。   
        pid = -1 : 将信号传送给系统内所有的进程。   
        pid < -1 : 将信号传给指定进程组的所有进程。这个进程组号等于 pid 的绝对值。   
    sig : 信号的编号，这里可以填数字编号，也可以填信号的宏定义，可以通过命令 kill - l("l" 为字母)进行相应查看。不推荐直接使用数字，应使用宏名，因为不同操作系统信号编号可能不同，但名称一致。   
​
返回值：   
    成功：0   
    失败：-1   

只能向自己创建的进程发送信号  

### int raise(int sig)
头文件：   
    #include <signal.h>   
功能：给当前进程发送指定信号(自己给自己发)，等价于 kill(getpid(), sig)    
参数：   
    sig：信号编号   
返回值：   
    成功：0   
    失败：非0值   


### void abort(void)
头文件：   
    #include <stdlib.h>   
功能：给自己发送异常终止信号 6) SIGABRT，并产生core文件，等价于kill(getpid(), SIGABRT);    
​
参数：无   
​
返回值：无    
​

### unsigned int alarm(unsigned int seconds)
头文件：   
    #include <unistd.h>   
功能：   
    设置定时器(闹钟)。在指定seconds后，内核会给当前进程发送14）SIGALRM信号。进程收到该信号，默认动作终止。每个进程都有且只有唯一的一个定时器。    
    取消定时器alarm(0)，返回旧闹钟余下秒数。    
参数：    
    seconds：指定的时间，以秒为单位    
返回值：   
    返回0或剩余的秒数    

​定时，与进程状态无关(自然定时法)！就绪、运行、挂起(阻塞、暂停)、终止、僵尸……无论进程处于何种状态，alarm都计时。   


### int setitimer(int which,  const struct itimerval *new_value, struct itimerval *old_value)
头文件：   
    #include <sys/time.h>   
功能：    
    设置定时器(闹钟)。 可代替alarm函数。精度微秒us，可以实现周期定时。    
参数：    
    which：指定定时方式    
        a) 自然定时：ITIMER_REAL → 14）SIGALRM计算自然时间    
        b) 虚拟空间计时(用户空间)：ITIMER_VIRTUAL → 26）SIGVTALRM  只计算进程占用cpu的时间   
        c) 运行时计时(用户 + 内核)：ITIMER_PROF → 27）SIGPROF计算占用cpu及执行系统调用的时间   
    new_value：struct itimerval, 负责设定timeout时间    
        ```
        struct itimerval {     
            struct timerval it_interval; // 闹钟触发周期     
            struct timerval it_value;    // 闹钟触发时间   
        };   
        struct timeval {    
            long tv_sec;            // 秒    
            long tv_usec;           // 微秒    
        }    
        itimerval.it_value： 设定第一次执行function所延迟的秒数     
        itimerval.it_interval：  设定以后每几秒执行function
        ```   
​
    old_value： 存放旧的timeout值，一般指定为NULL     
返回值：    
    成功：0   
    失败：-1    


### 信号集函数
```c
#include <signal.h>  
​
int sigemptyset(sigset_t *set);       //将set集合置空
int sigfillset(sigset_t *set)；          //将所有信号加入set集合
int sigaddset(sigset_t *set, int signo);  //将signo信号加入到set集合
int sigdelset(sigset_t *set, int signo);   //从set集合中移除signo信号
int sigismember(const sigset_t *set, int signo); //判断信号是否存在
```
> 参考代码[case_7.c](case_7.c)

### int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
头文件：   
    #include <signal.h>   
功能：    
    检查或修改信号阻塞集，根据 how 指定的方法对进程的阻塞集合进行修改，新的信号阻塞集由 set 指定，而原先的信号阻塞集合由 oldset 保存。   
​
参数：   
    how : 信号阻塞集合的修改方法，有 3 种情况：   
        SIG_BLOCK：向信号阻塞集合中添加 set 信号集，新的信号掩码是set和旧信号掩码的并集。相当于 mask = mask|set。   
        SIG_UNBLOCK：从信号阻塞集合中删除 set 信号集，从当前信号掩码中去除 set 中的信号。相当于 mask = mask & ~ set。   
        SIG_SETMASK：将信号阻塞集合设为 set 信号集，相当于原来信号阻塞集的内容清空，然后按照 set 中的信号重新设置信号阻塞集。相当于mask = set。   
    set : 要操作的信号集地址。   
        若 set 为 NULL，则不改变信号阻塞集合，函数只把当前信号阻塞集合保存到 oldset 中。   
    oldset : 保存原先信号阻塞集地址  
​
返回值：   
    成功：0，   
    失败：-1，失败时错误代码只可能是 EINVAL，表示参数 how 不合法。    


### int sigpending(sigset_t *set)
头文件：   
    #include <signal.h>   
功能：    
    读取当前进程的未决信号集   
参数：   
    set：未决信号集   
返回值：   
    成功：0   
    失败：-1   


### int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
头文件：   
    #include <signal.h>   
​功能：    
    检查或修改指定信号的设置（或同时执行这两种操作）。  
​
参数：  
    signum：要操作的信号。   
    act：   要设置的对信号的新处理方式（传入参数）。  
    oldact：原来对信号的处理方式（传出参数）。  
​
    如果 act 指针非空，则要改变指定信号的处理方式（设置），如果 oldact 指针非空，则系统将此前指定信号的处理方式存入 oldact。  
​
返回值：  
    成功：0   
    失败：-1   

struct sigaction结构体定义 
```c
struct sigaction {
    void(*sa_handler)(int); //旧的信号处理函数指针
    void(*sa_sigaction)(int, siginfo_t *, void *); //新的信号处理函数指针
    sigset_t   sa_mask;      //信号阻塞集
    int        sa_flags;     //信号处理的方式
    void(*sa_restorer)(void); //已弃用
};

1) sa_handler、sa_sigaction：信号处理函数指针，和 signal() 里的函数指针用法一样，应根据情况给sa_sigaction、sa_handler 两者之一赋值，其取值如下：
a) SIG_IGN：忽略该信号
b) SIG_DFL：执行系统默认动作
c) 处理函数名：自定义信号处理函数

2) sa_mask：信号阻塞集，在信号处理函数执行过程中，临时屏蔽指定的信号。

3) sa_flags：用于指定信号处理的行为，通常设置为0，表使用默认属性。它可以是一下值的“按位或”组合：
Ø SA_RESTART：使被信号打断的系统调用自动重新发起（已经废弃）
Ø SA_NOCLDSTOP：使父进程在它的子进程暂停或继续运行时不会收到 SIGCHLD 信号。
Ø SA_NOCLDWAIT：使父进程在它的子进程退出时不会收到 SIGCHLD 信号，这时子进程如果退出也不会成为僵尸进程。
Ø SA_NODEFER：使对信号的屏蔽无效，即在信号处理函数执行期间仍能发出这个信号。
Ø SA_RESETHAND：信号处理之后重新设置为默认的处理方式。
Ø SA_SIGINFO：使用 sa_sigaction 成员而不是 sa_handler 作为信号处理函数。

/**
 * 信号处理函数:
 */
void(*sa_sigaction)(int signum, siginfo_t *info, void *context);
参数说明：
    signum：信号的编号。
    info：记录信号发送进程信息的结构体。
    context：可以赋给指向 ucontext_t 类型的一个对象的指针，以引用在传递信号时被中断的接收进程或线程的上下文。
```


### int sigqueue(pid_t pid, int sig, const union sigval value)
头文件：   
    #include <signal.h>   
​功能：    
    给指定进程发送信号。
参数：
    pid : 进程号。   
    sig : 信号的编号。  
    value : 通过信号传递的参数。   
```c
// union sigval 类型如下：
union sigval
{
    int   sival_int;
    void *sival_ptr;
};
```   
返回值：   
    成功：0   
    失败：-1  