结构体
===

## 知识点
### 结构体的定义
* 使用`struct xx {};`定义，括号后一定要加分号`;`
* 定义结构体时成员不用赋值，且拥有独立的空间。

定义结构体的三种方式，推荐第一种
```c
// 先定义类型，在定义变量
struct stu {
    int num;
};

// 定义类型时 一并定义变量
struct stu {
    int num;
}lucy;

// 一次性结构体，不能再定义变量
struct {
    int num;
}lucy;
```

### 结构体赋值
* 采用字面量赋值`struct stu lucy = {100, "xxx"};`
* 指定字段`lucy.num = 100; strcpy(lucy.name, "xxx");`
* 内存拷贝`memcpy(&lucy, *bob, sizeof(struct stu));`
> 在内存操作前记得使用`memset`进行清0操作。
