数组
===

## 知识点
* 一维数组的名字就是数组的第0个元素的地址；
* 函数返回值小于等于4字节放寄存器；否则放在栈；
* `extern int data` 申明一个变量，后面再使用和赋值, 只有当前源文件有效；
* `extern` 其他源文件使用该全局变量 必须加该关键字；

### 初始化
数组初始化可以全部初始化，或部分初始化。当部分初始化时，其他为初始化的部分的值将会变成该类型的默认值;
```
int arr[3] = {10, 20};
printf("%d \n", arr[2]); // 0
```
> `int arr[5] = {[2] = 3, [4] = 7};` 表示从下标0开始，第三个元素值为3, 第五个为7。即 0 0 3 0 7

### 求数组中的个数
```
int arr[] = {10, 20, 30};
int d = sizeof(arr) / sizeof(arr[0]);
for (int i = 0; i < d; i++) {
    // todo
}
```
* `sizeof(arr)` 数组总大小，即元素个数 * 元素的大小


### 多维数组
二维数组的初始化分两种

* 分段初始化 `int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};` 用`{}`明确表示每一行;
* 连续初始化 `int arr[3][4] = {1, 2, 3, 4, 5};` 放满第一行才能放下一行;

计算时取值也是从0开始。
详细参考 [array_3.c](array_3.c)

### 字符串
字符串使用的是char[]，有两种初始化方法，`char s[6]="hello"` 和 `char s[6] = {'h', 'e', 'l'}`    
而打印方式也是两种，遍历`printf("%c", s[0])` 和 `printf("%s", s)`

#### 字符串的切割
可以通过数组+1的形式确定开头
```
    char word[10] = "allocated";
    printf("%s \n", word); // allocated
    // 不要前3个字母
    printf("%s \n", word + 3); // ocated

    // 不要后3个字母 - API
    char cut[10] = {0};
    strncpy(cut, word, strlen(word) - 3 ); // alloca
    printf("%s \n", cut);
    
    // 不要后3个字符 - 字符串指针
    memset(cut, 0, 10);
    char *start = word;
    char *end = word + (strlen(word) - 3);
    strncpy(cut, start, end - start);
    printf("%s \n", cut); // alloca
```

详细参考[array_5.c](array_5.c)   