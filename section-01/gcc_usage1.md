gcc使用指南1
===

多文件怎么手动gcc编译

### 多文件（分文件）编程 规范
* 把函数声明、宏放在头文件`xxx.h`中，并在主函数中包含相应头文件；
* 在头文件对应的`xxx.c`中实现`xxx.h`声明的函数。

### 防止头文件重复包含
#### 方法1： #pragma once
```c
#pragma once
```
编译器上统一设置

#### 方法2：#define
```c
#ifndef __SOMEFILE_H__
#define __SOMEFILE_H__

extern void* func(int, int);

#endif
```
使用代码进行

### 编译过程
```shell
gcc -o dist/a -I . func.c func_main.c
```
* `-I` 包含的头文件， 传入一个目录

多文件采用依赖的形式，逐步编译，最后编译main函数

```shell
./dist/a
20
```

### 文件结构

#### func.h
```c
int max(int, int);
```

#### func.c
```c
int max(int a, int b) {
    return a > b ? a: b;
}
```

#### func_main.c
```c
#include <stdio.h>
#include "func.h"

int main(int argc, char* argv[]) {
    const int max_num = max(10, 20);
    printf("max num is %d", max_num);
    return 0;
}
```


