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

## 接口
使用`virtual`关键字实现,接口类只是一个功能声明，并不是功能实现，子类需要根据功能说明定义功能实现。 注意:除了析构函数外，其他声明都是纯虚函数。   
> 参考[../section-09/game.hpp](../section-09/game.hpp) 和 [../section-09/game.cc](../section-09/game.cc)    

## C++模板 - 泛型
c++提供了函数模板(function template.) 所谓函数模板，实际上是建立一个通用函数，其函数类型和形参类型不具体制定，用一个虚拟的类型来代表。这个通用函数就成为函数模板。凡是函数体相同的函数都可以用这个模板代替，不必定义多个函数，只需在模板中定义一次即可。在调用函数时系统会根据实参的类型来取代模板中的虚拟类型，从而实现不同函数的功能。    

c++提供两种模板机制:函数模板和类模板 类属 - 类型参数化，又称参数模板    

总结： 模板把函数或类要处理的数据类型参数化，表现为参数的多态性，成为类属。 模板用于表达逻辑结构相同，但具体数据元素类型不同的数据对象的通用行为。

> 参考代码[函数模板 - case_1.cc](case_1.cc)    

类模板和函数模板的定义和使用类似，使用如下:
```cpp
template<class NameType, class AgeType>
class Person
{
public:
    Person(NameType name, AgeType age)
    {
        this->mName = name;
        this->mAge = age;
    }
    void showPerson()
    {
        cout << "name: " << this->mName << " age: " << this->mAge << endl;
    }

public:
    NameType mName;
    AgeType mAge;
};
void test01()
{
    //Person P1("德玛西亚",18); // 类模板不能进行类型自动推导
    Person<string, int>P1("德玛西亚", 18);
    P1.showPerson();
}
```

## 强制类型转换

### 静态转换 static_cast
```cpp
//子类指针转成父类指针,安全
Animal* animal02 = static_cast<Animal*>(dog01);

//父类指针转成子类指针，不安全
Dog* dog02 = static_cast<Dog*>(animal01);
```

### 动态转换 dynamic_cast
```cpp
//子类指针转换成父类指针 可以
Animal* animal02 = dynamic_cast<Animal*>(dog01);

//父类指针转换成子类指针 不可以
//Dog* dog02 = dynamic_cast<Dog*>(animal01);
```

### 常量转换 const_cast
```cpp
const int* p = NULL;
int* np = const_cast<int*>(p);
int* pp = NULL;
const int* npp = const_cast<const int*>(pp);
const int a = 10; //不能对非指针或非引用进行转换
//int b = const_cast<int>(a);
```

### 重新解释转换 reinterpret_cast
这是最不安全的一种转换机制，最有可能出问题。 主要用于将一种数据类型从一种类型转换为另一种类型。它可以将一个指针转换成一个整数，也可以将一个整数转换成一个指针。

## 异常
```cpp
调用，该函数默认行为调用 terminate 函数中断程序。
//可抛出所有类型异常
void TestFunction01(){
throw 10;
}
//只能抛出 int char char*类型异常
void TestFunction02() throw(int,char,char*){
string exception = "error!";
throw exception;
}
//不能抛出任何类型异常
void TestFunction03() throw(){
throw 10;
}
int main(){
try{
//TestFunction01();
//TestFunction02();
//TestFunction03();
}
catch (...){
cout << "捕获异常!" << endl;
}
}
system("pause");
```
> 参考代码[case_2.cc](case_2.cc)    
