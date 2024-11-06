动态内存分配与管理
===

## 知识点
* `malloc`申请内存， `free`释放内存；
* 若使用malloc申请的int*，无法使用指针遍历的方法，需要使用加角标的方式`ptr[i] = 1`进行赋值 或 `*(ptr+i) = 100;` 这两种方式；
* `calloc`申请数据块，地址连续，返回起始地址，空间自动清0；
* `realloc` 动态追加或减少空间。在原先s指向的内存基础上重新申请内存，新的内存的大小为`new_size`个 字节，如果原先内存后面有足够大的空间，就追加，如果后边的内存不够用，则realloc函数会在堆区找一个`new_size`个字节大小的内存申请，将原先内存中的内容拷贝过来，然后释放原先的内存，最后返回新内存的地址。 参数：s：原先开辟内存的首地址new_size：新申请的空间的大小，返回值：新申请的内存的首地址；注意：一定要保存**realloc的返回值**

## 示例代码
### 申请空间
```c
void test1() {
    int * addr = NULL;
    addr = (int*)malloc(sizeof(int)); // 申请空间需要强制类型转换，并且还需要指定请求的大小
    memset(addr, 0, sizeof(int)); // 对请求的空间进行清除操作
    *addr = 10087; // 使用
    printf("%d \n", *addr);
    // 防止多次释放
    if (addr != NULL) {
        free(addr); // 释放
        addr = NULL;
    }
}
```
> 代码参考[case_1.c](case_1.c)

注意：
* malloc 需要引入`stdlib.h`
* memset 需要引入`string.h`

### 申请块空间
```c
int* test2() {
    int* p = NULL;
    p = (int*) calloc(5, sizeof(int));
    if (NULL == p) {
        perror("calloc failed");
    }
    return p;
}
```
注意：
* calloc 不需要清0

### 追加内存空间
```c
int* append(*int oldP, int oldSize, int newSize) {
    return (int*) realloc(oldP, (oldSize + newSize) * sizeof(int));
}
```