gcc使用指南1
===

多文件怎么编译
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


