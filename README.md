C/CPP 练习与复习
===
> 温故而知新

**目录**

* [section-02](section-00/summary.md)
    * hello c
    * 键盘输入获取
* [section-01](section-01/summary.md)
    * 数组
    * [多文件编译](section-01/gcc_usage1.md)
    * 多维数组的初始化
* [section-02](section-02/summary.md)
    * 指针
    * 指针读取数组
    * 使用指针函数修改他范围外的值
    * 函数指针的动态调用
* [section-03](section-03/summary.md)
    * 动态内存的申请和释放
    * 数组类型的动态内存管理
* [section-04](section-04/summary.md)
    * [字符串API, 字符串提取、格式化输出、切割、查找、比较、复制、长度计算等](section-04/str_aip.md)
    * [字符串格式化API](section-04/str_atoi_api.md)
* [section-05](section-05/summary.md)
    * 结构体
    * [排序](section-05/case_2.c)
    * 枚举
* [section-06](section-06/summary.md)
    * 链表
    * [动态链表的插入、删除和查询](section-06/case_2.c)

## 环境准备
### 基础内容
```shell
sudo apt install gcc cmake gdb -y
```

### Visual Studio Code
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc build active file",
            "command": "/usr/bin/gcc",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-I ${fileDirname}",
                "-o",
                "${fileDirname}/dist/a"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ],
    "version": "2.0.0"
}
```

### vim
```vimrc
" DO NOT EDIT THIS FILE
" Add your own customizations in ~/.vim_runtime/my_configs.vim

set runtimepath+=~/.vim_runtime

source ~/.vim_runtime/vimrcs/basic.vim
source ~/.vim_runtime/vimrcs/filetypes.vim
source ~/.vim_runtime/vimrcs/plugins_config.vim
source ~/.vim_runtime/vimrcs/extended.vim
source ~/.vim_runtime/vimrcs/go-vim.vim
try
  source ~/.vim_runtime/my_configs.vim
catch
endtry
```
配置过程参考 https://github.com/amix/vimrc
