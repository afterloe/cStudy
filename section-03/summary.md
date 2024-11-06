动态内存分配与管理
===

## 知识点
* `malloc`申请内存， `free`释放内存;

## 示例代码
### 申请空间
```c
void test1() {
    int * addr = NULL;
    addr = (int*)malloc(sizeof(int)); // 申请空间需要强制类型转换，并且还需要指定请求的大小
    memset(addr, 0, sizeof(int)); // 对请求的空间进行清除操作
    *addr = 10087; // 使用
    printf("%d \n", *addr);
    free(addr); // 释放
}
```
> 代码参考[case_1.c](case_1.c)

注意：
* malloc 需要引入`stdlib.h`
* memset 需要引入`string.h`
