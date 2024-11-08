文件API
===

## 重点
### 打开文件

#### c
`FILE* fopen(const char* filePath, const char* type)`
* type: r,rb,w,wb,a,ab
* b -> 二进制的方式打开文件， + -> 以可读可写的方式打开
代码示例[case_1.c](case_1.c)

#### kernel
`int open(const char* filePath, const char* type)`
代码示例[kernel_case_1.c](kernel_case_1.c)

### 写文件
`fputs(const char*, const FILE*)` 或 `fputc(const char, const FILE*)`  
代码示例[case_2.c](case_2.c) 或 [kernel_case_2.c](kernel_case_2.c)

使用`open(const *filepath, const int, const ...opt);` 创建文件时需要传入权限码，否则会出现没有权限的问题。    

> demo1: [cp文件](case_3.c)