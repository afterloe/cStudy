命令行下的翻译软件
===

## 数据格式

### txt
txt格式来自自己收集的，
```
#{key}
Trans:{val}
```
* key 表示 要翻译的内容
* val 表示 解释
例如
```
#allocated
Trans:n. 分配；划拨；已分配；拨付；下拨；分配值
```

### CSV
采用 CSV 文件存储所有词条数据，用 UTF-8 进行编码，用 Excel 的话，别直接打开，否则编码是错的。在 Excel 里选择数据，来自文本，然后设定逗号分割，UTF-8 编码即可。

| 字段  |	解释  |
| ---- | ------- |
| word |	单词名称
| phonetic |	音标，以英语英标为主
| definition |	单词释义（英文），每行一个释义
| translation |	单词释义（中文），每行一个释义
| pos |	词语位置，用 "/" 分割不同位置
| collins |	柯林斯星级
| oxford |	是否是牛津三千核心词汇
| tag |	字符串标签：zk/中考，gk/高考，cet4/四级 等等标签，空格分割
| bnc |	英国国家语料库词频顺序
| frq |	当代语料库词频顺序
| exchange |	时态复数等变换，使用 "/" 分割不同项目，见后面表格
| detail |	json 扩展信息，字典形式保存例句（待添加）
| audio |	读音音频 url （待添加）

## 思路
使用链表作为数据结构将其加载到内存中，然后使用字符串匹配key的方式找到对应的翻译内容.     

* char数组首字母的移动可以快速截取字符串
* 借助strlen可以动态的申请空间，避免浪费
* sscanf可以去除不需要的字符，也可以通过移动char来实现.

## 重点API
* fopen, fclose, feof
* fgets, sscanf, strstr, strcpy, strlen

```c
void trim(char *buf)
{
    int n = strlen(buf) - 1;
    while (buf[n] == ' ' || buf[n] == '\n' || buf[n] == '\r' || buf[n] == '\t')
        n--;
    buf[n + 1] = 0;
}
```