Linux 网络编程
===

Socket本身有“插座”的意思，在Linux环境下，用于表示进程间网络通信的特殊文件类型。本质为内核借助缓冲区形成的伪文件

## 字节序大小端转换
为使网络程序具有可移植性，使同样的C代码在大端和小端计算机上编译后都能正常运行，可以调用以下库函数做网络字节序和主机字节序的转换。

## Socket Server && Client

`socket()`打开一个网络通讯端口，如果成功的话，就像 open()一样返回一个文件描述符，应用程序可以像读写文件一样用 read/write 在网络上收发数据，如果 socket()调用出错则返回-1。   
* 对于 IPv4，domain 参数指定为 AF_INET。   
* 对于 TCP 协议，type 参数指定为 SOCK_STREAM，表示面向流的传输协议。如果是 UDP 协议，则 type 参数指定为 SOCK_DGRAM，表示面向数据报的传输协议。
* protocol 参数的介绍从略，指定为 0 即可

重点api 可以参考 [socket_api.md](./socket_api.md)

### TCP
设置 socket 类型为 `SOCK_STREAM`， 需要绑定并进行监听，并在监听的时候调用`accetp`函数获取客户端，最后通过`write`方法实现通信。

代码参考:
[IPV6 TCP Server](case_3.c) / [IPV6 TCP Client](case_4.c)       

测试工具`telnet ip port`
> eg: IPV6 `telnet ::1 9200` 或 IPV4 `telnet 0.0.0.0 9291`

### UDP
设置 socket 类型为 `SOCK_DGRAM`，需要绑定即可，不用监听就能启动服务！读取参考如下代码
```c
struct sockaddr_in cli;
socklen_t len=sizeof(cli);
char chunk[1500] = {0};
while(1)
{
    memset(chunk, 0, 1500);
    recvfrom(sockfd, chunk, sizeof(chunk), 0, (struct sockaddr*)&cli, &len);
    printf("recv num =%s \n", chunk);
    sendto(sockfd, chunk, sizeof(chunk), 0, (struct sockaddr*)&cli, len);
}

close(sockfd);
```
代码参考:
[IPV6 TCP Server](case_3.c) / [IPV6 TCP Client](case_4.c)       

测试工具`nc`
> eg: IPV6 `nc -l -u ::1 9300`或 IPV4 `nc -l -u 127.0.0.1 9301`

## 高并发服务器

使用多进程并发服务器时要考虑以下几点：

1. 父进程最大文件描述个数(父进程中需要 close 关闭 accept 返回的新文件描述符)
2. 系统内创建进程个数(与内存大小相关)
3. 进程创建过多是否降低整体服务性能(进程调度)
4. 调整进程内最大文件描述符上限
5. 线程如有共享数据，考虑线程同步
6. 服务于客户端线程退出时，退出处理。（退出值，分离态）
7. 系统负载，随着链接客户端增加，导致其它线程不能及时得到 CPU

## 多路I/O转接服务器
多路 IO 转接服务器也叫做多任务 IO 服务器。该类服务器实现的主旨思想是，不再由应用程序自己监视客户端连接，取而代之由内核替应用程序监视文件。

### SELECT
select 能监听的文件描述符个数受限于 FD_SETSIZE，一般为 1024，单纯改变进程打开的文件描述符个数并不能改变 select 监听文件个数。
1024 以下客户端时使用 select 是很合适的，但如果链接客户端过多，select 采用的是轮询模型，会大大降低服务器响应效率，不应在 select 上投入更多精力。

使用 SELECT 构建服务的大致流程：
1. 建立TCP ipv6链接
2. 绑定前设置socket支持复用`setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));`
3. 绑定并监听
4. 设置最大文件数和SELECT监听队列;
5. 循环，在SELECT中获取变动的文件，并分别判断类型并执行相关操作。

> 参考代码[case_5.c](case_5.c) / [相关API - SELECT](./socket_api.md)   

### PSELECT
和select基本差不多，但有下面三个区别：
* select函数使用的timeout参数是struct timeval(以秒和微秒表示)类型的，而pselect函数使用struct timespec(以秒或纳秒表示)
* select可以更新timeout参数以指示剩余的时间。pselect的timeout参数声明为const确保其不会更改此参数。
* pselect可以选择使用的信号屏蔽字。若sigmask为空，那么在与信号有关的方面，pselect的运行状况和select相同。否则，sigmask指向一信号屏蔽字，在调用pselect时，以原子操作的方式安装该信号屏蔽字。在返回时恢复以前的信号屏蔽字。

> [相关API - SELECT](./socket_api.md)   

### POLL
如果不再监控某个文件描述符时，可以把 pollfd 中，fd 设置为-1，poll 不再监控此 pollfd，下次返回时，把 revents
设置为 0。   
相较于 select 而言，poll 的优势：   
1. 传入、传出事件分离。无需每次调用时，重新设定监听事件。  
2. 没有最大文件描述符数量的限制, 能监控的最大上限数可使用配置文件调整, 但是数量过大后性能也是会下降。   

> 参考代码[case_6.c](case_6.c) / [相关API - SELECT](./socket_api.md)   