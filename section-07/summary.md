文件API
===

## 重点
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

### 写文件 fputc、fputs
`fputs(const char*, const FILE*)` 或 `fputc(const char, const FILE*)`  , FILE*可以使用stdio、stdout等。在kernel中，可以使用STDOUT_FILENO 进行。    
代码示例[case_2.c](case_2.c) 或 [kernel_case_2.c](kernel_case_2.c)

使用`open(const *filepath, const int, const ...opt);` 创建文件时需要传入权限码，否则会出现没有权限的问题。    

> demo1: [cp文件](case_3.c)

### 文件格式化读写 fprintf, fscanf
同sscanf和printf的参数。

### 文件的块读写 fread、fwrite

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