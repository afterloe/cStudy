字符串相关API
===

使用API 需要引入`string.h`文件

### 字符串长度
size_t strlen(const char *s);

### 字符串拷贝
char* strcpy(char* dest, const char* src);

### 前num个复制到字符串中
char* strncpy(char* dest, const char* src, const int num);
> 把src指向字符串的前num个复制到dest所指向的空间中

### 字符串拼接
char* strcat(char *dest, const char* src);

### 拼接前n个
char* strncat(char *dest, const char* src, const int num);

### 字符串比较
int strcmp(const char* s1, const char* s2);
> '> 0' 表示s1 > s2  '=0' 表示相同

### 字符串局部比较
int strncmp(const char* s1, const char* s2, const num);
> 比较前num个字符， '=0' 表示相同

### 字符查找
char* *strchr(const char* s, int c);
> 返回第一次出现c字符的地址，没有找到返回NULL

### 字符串查找
char* strstr(const char* s1, const char* s2);
> 从s1中返回第一次出现s2字符串的地址，没有找到返回NULL

### 字符串切割
char* strtok(char *str, const char* delim);

> 第一次切割： str必须指向要切割的字符串首元素地址 delim指向要切割的符号   
> 第2~n次切割：str必须指向NULL delim指向要切割的符号   

返回值：切割成功 返回切割到字符换片段的首元素地址 失败：NULL  

**不能切割字符串常量**

一般选择 char *arr[] 指针数组 来存放上面 独立的字符串的首元素地址     
使用参考[case_1](case_1.c).strtokTest()

### 格式化输出
int sprintf(char* buf, const char* formar, opt...);
> opt: 各个零散的数据
> 返回值：返回值的是组好的报文的实际长度（不包含'\0'）
使用参考[case_1](case_1.c).strFormat    

左侧补充0 ‘%02d’ 左对齐，长度为2,不够的补0

### 格式化提取
* scanf(char* dst) 终端输入提取
* sscanf(const char* src, const char* fmt, opt...) 字符串数组提取
* fscanf 文件提取
使用参考[case_1](case_1.c).strScanf

```
sscanf("1234 5678","1234 %d",&data1);//5678
sscanf("1234 5678","%*d %d",&data1);//5678
sscanf("1234 5678","%*s %d",&data1);//5678
```
> sscanf的高级用法1：使用%*s %*d 跳过提取的内容（不要提取的内容）

```
sscanf("12abc5678","%*5s%d", &data1);//5678
sscanf("12345678","%*2s%2d%*2d%s", &data2, buf);//data2=34 buf="78";
```
> sscanf的高级用法2：使用%[n]s %[n]d 提取指定宽度n的字符串或数据

```
sscanf("xxxx", "reg", buf);
```
> %[a-z] 提取a-z的字符串 %[aBc] 提取 a B c %[^abc] 只要不是a b c任何一个 都要, 正则表达式？