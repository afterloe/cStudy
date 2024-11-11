练习：读取配置文件，配置文件加解密
===

## 思路
### 读配置
构建一个链表用于存储配置信息   

使用fopen打开配置文件，然后再使用fgets的方法读取配置  
使用strtok对读取的内容进行切割，  再分别进行赋值

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