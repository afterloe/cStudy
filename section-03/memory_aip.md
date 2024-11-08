内存操作函数
===

## 重点

### 内存重置 memset
```
string.h

void* memset(void* p, int c, size_t n);
```
将p指向的区域内的n个空间重置成字符c。

### 内存拷贝 memcpy
```
string.h

void* memcpy(void* dest, void* src, size_t n);
```
拷贝src所指的内存内容的前n个字节到dest所值的内存地址上。

### 内存空间重叠时进行拷贝 memmove
```
string.h

void* memcpy(void* dest, void* src, size_t n);
```
memmove()功能用法和memcpy()一样，区别在于：dest和src所指的内存空间重叠时，memmove()仍然能处理，不过执行效率比memcpy()低些

### 比较两个指向内容的前n个字节 memcmp
```
string.h

int memcmp(const void* s1, const void* s2, size_t n);
```
比较s1和s2所指向内存区域的前n个字节

* 相等：=0
* 大于：>0
* 小于：<0

### 堆内存申请 malloc
```
stdlib.h

void* malloc(size_t size);
```
在内存的动态存储区(堆区)中分配一块长度为size字节的连续区域，用来存放类型说明符指定的类型。分配的内存空间内容不确定，一般使用memset初始化。    

size使用sizeof关键字进行设置

### 堆内存申请 calloc
```
stdlib.h

void* calloc(int n, size_t size);
```
申请数据块，地址连续，返回起始地址，空间自动清0。不用进行memset，size使用sizeof关键字进行设置

### 堆内存修改
```
stdlib.h

void* realloc(void* old, size_t size);
```
在原先s指向的内存基础上重新申请内存，新的内存的大小为`new_size`个 字节, 返回值：新申请的内存的首地址；注意：一定要保存**realloc的返回值**.

```c
int* append(*int oldP, int oldSize, int newSize) {
    return (int*) realloc(oldP, (oldSize + newSize) * sizeof(int));
}
```

### 堆内存释放 free
```
stdlib.h

void free(void* ptr);
```
释放ptr所指向的一块内存空间，ptr是一个任意类型的指针变量，指向被释放区域的首地址。对同一内存空间多次释放会出错。   

所以在进行释放前需要进行NULL判断。