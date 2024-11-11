练习：读取配置文件，配置文件加解密
===

## 思路
### 读配置
构建一个链表用于存储配置信息   

使用fopen打开配置文件，然后再使用fgets的方法读取配置  
使用strtok对读取的内容进行切割，  再分别进行赋值

### 加解密
#### 加密
```
char -> short
0000 0000 0010 0011   <<  4

0000 0010 0011 0000   |  0x8000

1000 0010 0011 0000   +  0000 ~ 1111

1000 0010 0011 1101
```
将char转换为short   
step 1：先将 读取的char 左移4位    
step 2：再将获得的内容， 与short的最大值（32767） + 1 即 32768，0x8000 进行或 `|` 操作， 完成统一符号位
step 3: 加上一个0 ～ 16，二进制范围[0000 ~ 1111], 0x10 之内的随机数

#### 解密
```
1000 0010 0011 1101 << 1
0000 0100 0111 1010 >> 5
0000 0000 0010 0011 short -> char
```
将short转化为char
step 1：左移1位 去除符号位
step 2：右移动5位。去除添加的随机数
step 3：将short转换为char

## 注意事项

* fgets 会把`\n` 带进来，所以使用`sscanf(buf, "%[^\n]", buf);`就可以去除`\n
`;
* 结构体内的`char*`需要去申请空间，否则不能接收任何值。

## 重点API
### 文件
* fopen
* fgets

### 字符串
* strtok 多次切割字符串
* sscanf 
* strchr 判断是否有指定字符
* strcpy


## 编译脚本
### cmake
```
mkdir build
cd build
cmake ..
make
```

### sh
```shell
#!/bin/bash

/usr/bin/c++ -fdiagnostics-color=always \
-I.\
`find ./ -maxdepth 1 -name '*.c'` \
-o dist/a

echo '编译完毕'
```