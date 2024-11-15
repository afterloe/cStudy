make命令
===

## 命令

| 参数 | 描述
| ---- | ----
| -f | make默认在工作目录中寻找名为GNUmakefile、makefile、Makefile的文件作为makefile输入文件 -f 可以指定以上名字以外的文件作为makefile输入文件
| -v | 显示make工具的版本信息
| -w | 在处理makefile之前和之后显示工作路径
| -C | dir：读取makefile之前改变工作路径至dir目录
| -n | 只打印要执行的命令但不执行
| -s | 执行但不显示执行的命令

> 若使用make命令时没有指定目标，则make工具默认会实现makefile文件内的第一个目标，然后退出。指定了make工具要实现的目标，目标可以是一个或多个（多个目标间用空格隔开）。

## 变量
makefile变量名可以以数字开头  
变量是大小写敏感的  
变量一般都在makefile的头部定义   
变量几乎可在makefile的任何地方使用  

定义变量方法   
`变量名=变量值`

引用变量   
`$(变量名)或${变量名}`

### 自动变量
```
$@: 表示规则中的目标
$<: 表示规则中的第一个条件
$^: 表示规则中的所有条件, 组成一个列表, 以空格隔开,如果这个列表中有重复的项则消除重复项。
```

eg:
```makefile
#变量
OBJS=add.o sub.o mul.o div.o test.o add.o
TARGET=test
CC=gcc
​
#$@: 表示目标
#$<: 表示第一个依赖
#$^: 表示所有的依赖
​
$(TARGET):$(OBJS)
    #$(CC) $(OBJS) -o $(TARGET) 
    $(CC) $^ -o $@
    echo $@
    echo $<
    echo $^
​
add.o:add.c
    $(CC) -c $< -o $@ 
​
sub.o:sub.c
    $(CC) -c $< -o $@ 
​
mul.o:mul.c
    $(CC) -c $< -o $@ 
​
div.o:div.c
    $(CC) -c $< -o $@ 
​
test.o:test.c
    $(CC) -c $< -o $@
​
clean:
    rm -rf $(OBJS) $(TARGET)
```
> $(CC) 系统变量 = gcc

模板规则
```
%.o:%.c

$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
```

## 函数

* wildcard
查找指定目录下的指定类型的文件
```makefile
src = $(wildcard *.c)
```
找到当前目录下所有后缀为.c的文件,赋值给src

* patsubst
匹配替换
```makefile
obj = $(patsubst %.c, %.o, $(src))
```
把src变量里所有后缀为.c的文件替换成.o

eg:
```makefile
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRC))
TARGET=test
$(TARGET):$(OBJS)
    gcc $(OBJS) -o $(TARGET) 
​
%.o:%.c
    gcc -c $< -o $@
```
> 参考上面的`模板规则`


## 伪目标
.PHONY:xx

eg:
```makefile
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRC))
TARGET=test
$(TARGET):$(OBJS)
    gcc $(OBJS) -o $(TARGET) 
​
%.o:%.c
    gcc -c $< -o $@

.PHONY:clean
clean:
    rm -rf $(OBJS) $(TARGET)
```
> “-”此条命令出错，make也会继续执行后续的命令。如:“-rm main.o”    
> “@”不显示命令本身,只显示结果。如:“@echo clean done”