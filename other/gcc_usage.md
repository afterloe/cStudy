GCC工具的使用
===

## 直接使用
```shell
gcc -fdiagnostics-color=always -o dist/a.out -I. func.c main.c
```
* -o 成果文件放置位置
* -I 头文件
* opt... 需要编译的文件

 | 选项 | 含义 |
 | --- | ---- |
 | -o file | 指定生成的输出文件名为file |
 | -E | 只进行预处理 |
 | -S | 只进行预处理和编译 |
 | -c | 只进行预处理、编译和汇编 |
 | -Wall | 显示所有警告信息 |
 | -Werror | 所有警告信息当错误处理
 | -g | 包含调试信息
 | -On n=0~3 | 编译优化，n越大，优化越多
 | -D | 编译时定义宏 [代码](../section-00/case_0.c)， 前提是宏，没有被定义
 | -fdiagnostics-color=always | 异常信息显示颜色
 | -static | 采用静态连接编译，文件大
 | -L | 库所在的目录
 | -I | 头文件所在的目录
 | -l (小写L) | 指定链接时需要的库，去掉前缀和后缀


## 静态连接和动态连接
### 静态链接
静态链接：由链接器在链接时将库的内容加入到可执行程序中。

### 动态链接
动态链接：连接器在链接时仅仅建立与所需库函数的之间的链接关系，在程序运行时才将所需资源调入可执行程序

### 编译时指定
```shell
gcc test.c -o test_share
gcc -static test.c -o test_static
```

## 库制作
### 静态库
静态库的优势: `对运行环境的依赖性较小，具有较好的兼容性`    

静态库的缺点:
* 生成的程序比较大，需要更多的系统资源，在装入内存时会消耗更多的时间     
* 库函数有了更新，必须重新编译应用程序


命名规则：   
前缀：lib   
库名称：自己定义即可   
后缀：.a   

#### 以*test*为例子进行静态库制作

step1： 将c源码 生成对应的 .o 文件    
 
编译
```shell
gcc -c add.c -o add.o
gcc -c sub.c -o sub.o 
gcc -c mul.c -o mul.o 
gcc -c div.c -o div.o
```

step2: 打包    
```shell
ar -rcs libtest.a add.o sub.o mul.o div.o
```
> 参数说明 r更新 c创建 s建立索引

step3: 使用*test*静态库   

静态库制作完成之后，需要将.a文件和头文件一起发布给用户。   
```shell
gcc test.c -L./ -I./ -ltest -o test
```
>-L：表示要连接的库所在目录 -I./: I(大写i) 表示指定头文件的目录为当前目录 -l(小写L)：指定链接时需要的库，去掉前缀和后缀


### 动态库
动态库的优势  
1)在需要的时候才会调入对应的资源函数;    
2)简化程序的升级；有着较小的程序体积;    
3)实现进程之间的资源共享（避免重复拷贝）       

动态库的缺点   
* 依赖动态库，不能独立运行
* 动态库依赖版本问题严重

命名规则：   
前缀：lib   
库名称：自己定义即可   
后缀：.so

#### 制作动态库

step1: 编译    
```
gcc -fPIC -c add.c
gcc -fPIC -c sub.c
gcc -fPIC -c mul.c
gcc -fPIC -c div.c
```
> -fPIC 创建与地址无关的编译程序（pic，position independent code），是为了能够在多个应用程序间共享   

step2: 打包并生存共享库
```
gcc -shared add.o sub.o mul.o div.o -o libtest.so
```
> 生成共享库，此时要加链接器选项: -shared（指定生成动态链接库）

step3: 检查动态库   

使用`nm`查看对应的函数
```shell
nm libtest.so | grep add

00000000000006b0 T add
```

使用`ldd`查看可执行文件的依赖的动态库
```shell
ldd test linux-vdso.so.1

(0x00007ffcf89d4000) libtest.so => /lib/libtest.so (0x00007f81b5612000) libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f81b5248000) /lib64/ld-linux-x86-64.so.2 (0x00005562d0cff000)
```

#### 动态库使用
编译:
```
gcc test.c -L. -I. -ltest
```
> 参数描述同静态库

因未关联动态库会出现报错。

#### 让系统关联动态库
有四种方法进行关联
* 1） 拷贝自己制作的共享库到`/lib`或`/usr/lib`下(不能是/lib64目录)，或者使用`ln -s` 创建符号连接符;   
* 2）临时设置LD_LIBRARY_PATH `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径`;   
* 3） 永久设置,把`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径`，设置到`~/.bashrc`或者 `/etc/profile`文件中;   
* 4） 将其添加到 `/etc/ld.so.conf`文件中,编辑`/etc/ld.so.conf`文件，加入库文件所在目录的路径, 运行`sudo ldconfig -v`，该命令会重建`/etc/ld.so.cache`文件。  