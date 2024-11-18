Socket API
===

## 重点API

### uint16_t htons(uint16_t hostlong)
头文件:   
    #include <arpa/inet.h>   
功能：
    将端口号换为字节序       
参数:    
    hostlong: 端口号   
返回值：   
    字节序

>eg `servadd.sin6_port = htons(9200)`



### uint32_t htonl(uint32_t hostlong)
头文件:   
    #include <arpa/inet.h>   
功能：
    将字节序转换为端口号       
参数:    
    hostlong: 网络字节序   
返回值：   
    端口号

>eg `ntohs(client.sin6_port)`
    

### int inet_pton (int domain, const char *addr, void *input)
头文件:   
    #include <arpa/inet.h>   
功能：
    将ip地址转换为字节序        
参数:    
    domain:   
        AF_INET 这是大多数用来产生 socket 的协议，使用 TCP 或 UDP 来传输，用 IPv4 的地址   
        AF_INET6 与上面类似，不过是来用 IPv6 的地址    
        AF_UNIX 本地协议，使用在 Unix 和 Linux 系统上，一般都是当客户端和服务器在同一台及其上的时候使用       
    addr: 地址， struct sockaddr的目标地址    
    input: 输入的地址，例如"127.0.0.1"    
返回值：     
    成功：返回指向新创建的 socket 的文件描述符    
    失败：返回-1，设置 errno  

>eg `char ip[32] = ":::"; const char* addr = (const char*)&servadd.sin6_addr.s6_addr; inet_pton(AF_INET6, addr, ip);`    
> eg `inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);`


### const char * inet_ntop(int domain, const char *addr, char *buf, int bufsize)
头文件:   
    #include <arpa/inet.h>   
功能：
    将字节序转换为ip地址        
参数:    
    domain:   
        AF_INET 这是大多数用来产生 socket 的协议，使用 TCP 或 UDP 来传输，用 IPv4 的地址   
        AF_INET6 与上面类似，不过是来用 IPv6 的地址    
        AF_UNIX 本地协议，使用在 Unix 和 Linux 系统上，一般都是当客户端和服务器在同一台及其上的时候使用       
    addr: 地址， struct sockaddr的目标地址    
    buf: 读取的地址，例如"char client_ip[32] = { 0 }"     
    bufsize: 读取的地址的大小     
返回值：     
    ip的字符串

> eg: `char client_ip[32] = { 0 }; inet_ntop(AF_INET6, &client.sin6_addr.s6_addr, client_ip, sizeof(client_ip))`


详见代码[case_1.c](case_1.c); [点分制ip转换子节序](case_2.c);


### int socket(int domain, int type, int protocol)
头文件:   
    #include <sys/types.h> /* See NOTES */   
    #include <sys/socket.h>   
功能：
    创建一个Socket客户端   
参数:  
    domain:   
        AF_INET 这是大多数用来产生 socket 的协议，使用 TCP 或 UDP 来传输，用 IPv4 的地址   
        AF_INET6 与上面类似，不过是来用 IPv6 的地址    
        AF_UNIX 本地协议，使用在 Unix 和 Linux 系统上，一般都是当客户端和服务器在同一台及其上的时候使用    
    type:   
        SOCK_STREAM 这个协议是按照顺序的、可靠的、数据完整的基于字节流的连接。这是一个使用最多的 socket 类型，这个 socket是使用 TCP 来进行传输。   
        SOCK_DGRAM 这个协议是无连接的、固定长度的传输调用。该协议是不可靠的，使用 UDP 来进行它的连接。    
        SOCK_SEQPACKET 该协议是双线路的、可靠的连接，发送固定长度的数据包进行传输。必须把这个包完整的接受才能进行读取。     
        SOCK_RAW socket 类型提供单一的网络访问，这个 socket 类型使用 ICMP 公共协议。（ping、traceroute 使用该协议）    
        SOCK_RDM 这个类型是很少使用的，在大部分的操作系统上没有实现，它是提供给数据链路层使用，不保证数据包的顺序       
    protocol:    
        传 0 表示使用默认协议。     
返回值：     
    成功：返回指向新创建的 socket 的文件描述符    
    失败：返回-1，设置 errno    


### int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
头文件:   
    #include <sys/types.h> /* See NOTES */   
    #include <sys/socket.h>   
功能：
    绑定端口   
参数:  
    sockfd: socket 文件描述符    
    addr: 构造出 IP 地址加端口号   
    addrlen: sizeof(addr)长度    
返回值：   
    成功返回 0    
    失败返回-1, 设置 errno    

bind()的作用是将参数 sockfd 和 addr 绑定在一起，使 sockfd 这个用于网络通讯的文件描述符监听 addr 所描述的地址和端口号。struct sockaddr *是一个通用指针类型，addr 参数实际上可以接受多种协议的 sockaddr结构体，而它们的长度各不相同，所以需要第三个参数 addrlen 指定结构体的长度。 


### int listen(int sockfd, int backlog)
头文件:    
    #include <sys/types.h> /* See NOTES */   
    #include <sys/socket.h>   
功能：
    监听端口并启动服务   
参数:    
    sockfd: socket 文件描述符   
    backlog:  指定队列的最大长度，用于记录正在连接但尚未完成的客户端请求       
返回值：   
    成功返回 0    
    失败返回-1, 设置 errno        


### int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
头文件:    
    #include <sys/types.h> /* See NOTES */   
    #include <sys/socket.h>   
功能：接收客户端请求    
参数:    
    sockdf: socket 文件描述符    
    addr: 传出参数，返回链接客户端地址信息，含 IP 地址和端口号    
    addrlen: 传入传出参数（值-结果）,传入 sizeof(addr)大小，函数返回时返回真正接收到地址结构体的大小   
返回值：    
    成功返回一个新的 socket 文件描述符，用于和客户端通信    
    失败返回-1，设置 errno    


### int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
头文件:    
    #include <sys/types.h> /* See NOTES */   
    #include <sys/socket.h>   
功能：连接服务端    
参数:    
    sockdf: socket 文件描述符     
    addr: 传入参数，指定服务器端地址信息，含 IP 地址和端口号    
    addrlen: 传入参数,传入 sizeof(addr)大小    
返回值：    
    成功返回 0   
    失败返回-1，设置 errno   


### int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
头文件:    
    #include <sys/select.h> /* According to earlier standards */   
    #include <sys/time.h>    
    #include <sys/types.h>    
    #include <unistd.h>    
功能: 多路复用I/O - SELECT 模型
参数:    
    nfds:监控的文件描述符集里最大文件描述符加 1，因为此参数会告诉内核检测前多少个文件描述符的状态   
    readfds：监控有读数据到达文件描述符集合，传入传出参数   
    writefds：监控写数据到达文件描述符集合，传入传出参数   
    exceptfds： 监控异常发生达文件描述符集合,如带外数据到达异常，传入传出参数   
    timeout： 定时阻塞监控时间，3 种情况   
        1.NULL，永远等下去   
        2.设置 timeval，等待固定时间   
        3.设置 timeval 里时间均为 0，检查描述字后立即返回，轮询   
返回值：    
    成功返回 0   
    失败返回-1，设置 errno   

timeval 内容 和 FD 内容描述
```c
struct timeval
{
    long tv_sec; /* seconds, 秒 */
    long tv_usec; /* microseconds， 毫秒 */
}

void FD_CLR(int fd, fd_set *set);

//把文件描述符集合里 fd 位清 0
int FD_ISSET(int fd, fd_set *set); //测试文件描述符集合里 fd 是否置 1
void FD_SET(int fd, fd_set *set);//把文件描述符集合里 fd 位置 1
void FD_ZERO(fd_set *set);//把文件描述符集合里所有位清 0
```