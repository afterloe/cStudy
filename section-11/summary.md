Linux 网络编程
===

Socket本身有“插座”的意思，在Linux环境下，用于表示进程间网络通信的特殊文件类型。本质为内核借助缓冲区形成的伪文件

## 字节序大小端转换
为使网络程序具有可移植性，使同样的C代码在大端和小端计算机上编译后都能正常运行，可以调用以下库函数做网络字节序和主机字节序的转换。

```c
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong)
其中,hostlong是主机字节顺序表达的32位数，htonl中的h–host主机地址，to–to,n–net网络，l–unsigned long无符号的长整型(32位的系统是4字节)；
函数返回值是一个32位的网络字节顺序；
函数的作用是将一个32位数从主机字节顺序转换成网络字节顺序。

uint16_t htons(uint16_t hostlong)
其中,hostlong是主机字节顺序表达的16位数，htons中的h–host主机地址，to–to,n–net网络，s–signed long无符号的短整型(32位的系统是2字节)；
函数返回值是一个16位的网络字节顺序；
函数的作用是将一个16位数从主机字节顺序转换成网络字节顺序，简单的说就是把一个16位数高低位呼唤。

uint16_t ntohs(uint16_t hostlong)
其中,hostlong是网络字节顺序表达的16位数，ntohs中的,n–net网络，to–toh–host主机地址，s–signed long有符号的短整型(32位的系统是2字节)；
函数返回值是一个16位的主机字节顺序；
函数的作用是将一个16位数由网络字节顺序转换为主机字节顺序，简单的说就是把一个16位数高低位互换。

uint32_t ntohs(uint32_t hostlong)
其中,hostlong是网络字节顺序表达的32位数，ntohs中的,n–net网络，to–toh–host主机地址，s–unsigned long无符号的短整型(32位的系统是4字节)；
函数返回值是一个32位的主机字节顺序；
函数的作用是将一个32位数由网络字节顺序转换为主机字节顺序。
```
h表示host，n表示network，l表示32位长整数，s表示16位短整数。    

如果主机是小端字节序，这些函数将参数做相应的大小端转换然后返回，如果主机是大端字节序，这些函数不做转换，将参数原封不动地返回。
> 详见代码[case_1.c](case_1.c); [点分制ip转换子节序](case_2.c);


## Socket Server && Client

`socket()`打开一个网络通讯端口，如果成功的话，就像 open()一样返回一个文件描述符，应用程序可以像读写文件一样用 read/write 在网络上收发数据，如果 socket()调用出错则返回-1。   
* 对于 IPv4，domain 参数指定为 AF_INET。   
* 对于 TCP 协议，type 参数指定为 SOCK_STREAM，表示面向流的传输协议。如果是 UDP 协议，则 type 参数指定为 SOCK_DGRAM，表示面向数据报的传输协议。
* protocol 参数的介绍从略，指定为 0 即可


代码参考:
[IPV6 Server](case_3.c) / [IPV6 Client](case_4.c)    

重点api如下：

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