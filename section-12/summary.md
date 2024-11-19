c++与c的区别
===
c++是对C的扩展，因此c++是c语言的超集。文件使用cpp或cc结尾

## 头文件区别
```cpp
#include <iostream>
#include <cstring>
```
尽量不使用带`.h`的头文件, 转换规则`string.h` -> `cstring`，前面加`c`。

## 命名空间
```cpp
namespace A 
{
    bool flag = false;
    extern void funa(int, float b = 3.14);
}

void A::funa(int r, float pi = 3.14)
{
    ....
}
```
使用`::`域进行访问   
c++支持默认参数。 增加`bool`类型，`0 - 假， 非0为真`

## 输入输出优化

cin / cout 和 endline;
> 参考代码[../secton-00/hello.cc](../section-00/hello.cc)

cout 比 printf 差太多， 无论性能上还是使用方便上。

## struct 增强
c++中， struct 除了可以写成员变量，还能写函数。
> 参考代码[../section-02/print_array.cc](../section-02/print_array.cc)

## 引用
```cpp
extern printArray(void *&, int size);
```
等价于`printArray(void **, int size)`, 操作更便捷，更形象。

## 类和对象

类定义
```cpp
class xx{
public:
    virtual void Dese();
public:
    int mTall;
protected:
    int mMoney;
private:
    int mAge;
};
```
> 参考代码[../section-05/case_1.cc](../section-05/case_1.cc)