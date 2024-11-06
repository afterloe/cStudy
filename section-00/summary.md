section-1
===
## 知识点
### 数据类型
char、short、int、long、float、double    
int 1 = 0000 0001

### signed和unsigned
signed少一位，最高位为1表示复数，0表示正数

### register关键字
register 表示将 变量放入寄存器中，可实现高速读取，缺点就是不能对其进行取地址的操作

### typedef关键字
typeof关键字可以为已有的类型取个别名，例如`typedef int INT32;`，在使用的时候就是`INT32 a = 3;`

### 进制的问题
只是展示形式不同， %d 十进制； %#o 八进制； %#x 十六进制

## 练习
### hello iot
使用标准库 - std, 实现输出内容。

```c
#include <stdio.h>

int main(int argc, char** argv) {
    printf("hello iot");
    return 0;
}
```
代码[hello.c](hello.c)

### 求圆的面积
* `#define` 定义一个常量
* `scanf` 获取键盘输入

```c
#include <stdio.h>

#define PI 3.14

int main(int argc, char** argv) {
    float r;
    printf("please input r");
    scanf("%f", &r);
    const float area = PI * r * r;
    printf("area is %.2f", area);

    return 0;
}
```
代码[calculate_area.c](calculate_area.c)

## 函数调用
* 定义函数 `int add(int, int);`
* 函数实现
* 函数调用

```c
#include<stdio.h>

int add(int, int);

int main(int argc, char** argv) {
    printf("step 1: Enter first number \n");
    int a, b;
    scanf("%d", &a);
    printf("step 2: Enter second number \n");
    scanf("%d", &b);
    const int sum = add(a, b);
    printf("%d + %d = %d \n", a, b, sum);

    return 0;
}

int add(int a, int b) {
    return a + b;
}
```
代码[add_func.c](add_func.c)

### 编译
```shell
rm -rf dist
mkdir dist
gcc hello.c -o dist/hello
./dist/hello

hello ubuntu!
```
使用`gcc`进行编译， -o 指定输出目录，确保目录已经存在。
