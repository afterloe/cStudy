文件API
===

## 重点

### 文件状态 status
引入`sys/stat.h`，使用内置结构体`struct stat * p`接收。
```
struct stat *p;
stat(char *filepaht, p);


```
代码示例[文件状态](case_7.c)

### 文件重命名 rename

### 文件删除 remove

### 打开文件并读取 fopen、fclose、fgetc、fgets
`fgetc(int, FILE*)` int 为一个char， 当char不等于EOF，即-1表示任能继续读取。   
`fgets(char*, n, fp)`  n 为char[]的大小。
代码示例[cat文件](case_4.c)

`FILE* fopen(const char* filePath, const char* type)`
* type: r,rb,w,wb,a,ab
* `b` -> 二进制的方式打开文件， `+` -> 以可读可写的方式打开
代码示例[case_1.c](case_1.c)

#### kernel的方式打开文件 open、close、write、read
`int open(const char* filePath, const char* type)`
代码示例[kernel_case_1.c](kernel_case_1.c)

#### 读取乱码的问题
同一个文件写入然后又读取会出现读取乱码的问题，原因在于文件写完后需要关闭文件，然后重新打开文件，让文件流指针 重新指向开始位置。若不想进行此次操作可以使用复位文件流指针函数`rewind(*FILE)`来进行。
```c
fp = fopen();
fwrite(content, sizeof(content), 2, fp);
rewind(fp); // 复位文件流
fread(content, sizeof(content), 2, fp);
```    

### 获取文件流指针所在的位置 ftell
当前指针到头部的位置使用函数`int ftell(*FILE)`，该函数返回当前位置距离文件起始的字节数。
> 骚操作， 使用fseek将指针移到文件末尾，在调用ftell，就可以返回该文件的字节大小了。

计算文件有多少行`fgetc() == '\n'; line++` 计算 字符有多少个`\n`即可。   

### 指定读写位置 fseek
fseek函数一般用于二进制文件
```
int fseek(*FILE, n, w);

n: 偏移量, 负数左移，正数右移
w: 
   SEEK_SET 0 文件开头
   SEEK_CUR 1 文件当前位置
   SEEK_END 2 文件末尾

以w为起点，移动n个单位
```

### 判断文件是否到达末尾 feof
EOF宏只适用于文本文件，`feof(*FILE)`适用于所有文件。

### 写文件 fputc、fputs
`fputs(const char*, const FILE*)` 或 `fputc(const char, const FILE*)`  , FILE*可以使用stdio、stdout等。在kernel中，可以使用STDOUT_FILENO 进行。    
代码示例[case_2.c](case_2.c) 或 [kernel_case_2.c](kernel_case_2.c)

使用`open(const *filepath, const int, const ...opt);` 创建文件时需要传入权限码，否则会出现没有权限的问题。    

> demo1: [cp文件](case_3.c)

### 文件格式化读写 fprintf, fscanf
同sscanf和printf的参数。

### 文件的块读写 fread、fwrite
也可以用着一块进行大文件的读写操作，加了buf会比putc和getc快很多

#### fwrite
```
fwrite(buffer, size, count, fp);

buffer: 结构体首地址指针 arr
size: 结构体的大小 sizeof(struct)
count: 要读写的数据块个数 sizeof(arr) / sizeof(struct)
fp 
```
可以理解为数据序列化， [代码示例](case_5.c)

#### fread
```
fread(buffer, size, count, fp);

buffer: 结构体首地址指针 arr
size: 结构体的大小 sizeof(struct)
count: 要读写的数据块个数 sizeof(arr) / sizeof(struct)
fp
```
可以理解为数据反序列化，[代码示例](case_6.c)

### 更新缓冲区 fflush
```
stdio.h

int fflush(FILE*);
```
更新缓冲区，让缓冲区的数据立马写到文件中。