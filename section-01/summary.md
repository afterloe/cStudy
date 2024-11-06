数组
===

## 知识点

### 求数组中的个数
```
int arr[] = {10, 20, 30};
int d = sizeof(arr) / sizeof(arr[0]);
for (int i = 0; i < d; i++) {
    // todo
}
```
* `sizeof(arr)` 数组总大小，即元素个数 * 元素的大小
