Linux下常用工具
===

## Socket 模拟工具 - nc
模拟tcp客户端，测试tcp服务端是否正常运行。
```
nc 127.0.0.1 8000
```
> tcp client 连接 127.0.0.1:8000 端口  
```
nc 127.1 8000
```
> 在本机上使用 可以用上面的方法，效果等价与第一类

```
nc -u 127.1 8888
```
> 模拟udp客户端

```
nc -U foo.socket
```
> 模拟uds客户端

## 内存泄漏检测工具 - valgrind
### 工具安装
```
sudo apt install valgrind -y
```

### 编译可执行文件并调用工具进行检测
```
// 携带调试信息
gcc -g test.c -o test.app

// 进行检测
valgrind --tool=memcheck ./test.app

==1424920== HEAP SUMMARY:
==1424920==     in use at exit: 32 bytes in 2 blocks
==1424920==   total heap usage: 6 allocs, 4 frees, 1,360 bytes allocated
```
一般情况下， `allocs`的值与`frees`的值相同，如果不同，则显示存在泄漏。

### 显示泄露位置
```
valgrind --tool=memcheck --leak-check=full ./test.app
```