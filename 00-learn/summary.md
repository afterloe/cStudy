section-1
===

## hello iot
使用标准库 - std, 实现输出内容。

```c
#include <stdio.h>

int main(int argc, char** argv) {
    printf("hello iot");
    return 0;
}
```
代码[hello.c](hello.c)

## 求圆的面积
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

## 编译
```shell
rm -rf dist
mkdir dist
gcc hello.c -o dist/hello
./dist/hello

hello ubuntu!
```
使用`gcc`进行编译， -o 指定输出目录，确保目录已经存在。
