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