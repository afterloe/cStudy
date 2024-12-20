目录
===

* [section-00](section-00/summary.md)
    * hello c
    * 键盘输入获取
    * 位操作 - 不借助第三数值实现两个数交换
    * [生成随机数](section-00/case_1.c)
* [section-01](section-01/summary.md)
    * 数组
    * [多文件（分文件）编程](section-01/gcc_usage1.md)
    * 多维数组的初始化
* [section-02](section-02/summary.md)
    * 指针与万能指针void*
    * 指针读取数组
    * 使用指针函数修改他范围外的值
    * 函数指针的动态调用，回调函数
* [section-03](section-03/summary.md)
    * 动态内存的申请和释放
    * 数组类型的动态内存管理
    * [内存操作函数](section-03/memory_aip.md)
* [section-04](section-04/summary.md)
    * [字符串API, 字符串提取、格式化输出、切割、查找、比较、复制、长度计算等](section-04/str_aip.md)
    * [字符串格式化API](section-04/str_atoi_api.md)
* [section-05](section-05/summary.md)
    * 结构体及深拷贝和浅拷贝
    * 枚举
* [section-06](section-06/summary.md)
    * 文件读写操作, 文件指针的移动
    * 文件状态、文件重命名及文件删除
* [section-07 数据结构](section-07/summary.md)
    * 数据结构
    * [线性表](section-07/linear-list/summary.md)/ [链表的插入、删除和查询](section-07/linear-list/case_2.c)/ 链表的反转
    * 动态数组
    * 动态链表
    * 栈 / 队列
    * 树 / 二叉树
    * 图
* [section-08 查询与算法](section-08/summary.md)
    * 查询 / 二叉树查询 
    * [冒泡排序](section-05/case_2.c)
    * [选择排序](section-07/linear-list/case_3.c)
    * [插入排序](section-08/case_1.c)
* [section-09 面向接口编程](section-09/summary.md)
    * 定义函数指针
    * 定义实现函数指针的函数
    * 实现函数
    * 调用
* [section-10 Linux C](section-10/summary.md)
    * 系统调用 / 错误处理 / [系统调用相关API](section-10/system_invoke_api.md)
    * 进程 / 通道 / 进程控制模块PCB / [进程相关API](section-10/thread_api.md)
    * 进程通信 / 管道流 / 共享存储映射
    * 信号 / 信号捕捉和处理 / PV操作  / [相关API](section-10/pv_option_api.md)
    * 守护进程 / 线程 / [线程池相关API](section-10/thread_pool_api.md)
    * 锁 / 条件变量 / 生产者消费者条件变量模型 / [相关API](section-10/mutex_api.md)
* [section-11 Socket c](section-11/summary.md)
    * MAC / IP / Socket / TCP / UDP / [Socket API](section-11/socket_api.md)
    * 多路IO / SELECT / POLL / EPOLL  / 反应堆线程池 
    * [libevent](section-11/case_12_libevent)
* [section-12 C&Cpp 混合应用](section-12/summary.md)
    * c++基础语法 / 与c混合编译 / 静-动态库的调用
    * [ffmpeg 获取音频信息](section-12/ffmpeg/case_5.c) / [mp3 解码](section-12/ffmpeg/case_8.c) / [flac 解码](section-12/ffmpeg/case_9.c)
    * [SDL2 播放解码后的音频](section-12/ffmpeg/case_7.c)
    * [ffmpeg + SDL2 直接播放 flac](section-12/ffmpeg/case_10.c)
    * [迷你音乐播放器](section-12/min_player/minplayer.c)
    * [ASNSI屏幕控制](section-12/min_player/ANSI屏幕控制码.md)


* 备忘录
    * [C/C++注释](other/explanatory_note.md)
    * [GCC的使用以及库的创建和使用](other/gcc_usage.md)
    * [makefile和make](other/make_usage.md)
    * [libevent 网络工具库](other/libevent_usage.md)
    * [socket模拟工具、内存泄漏检测工具](other/tools.md)
    * [openssl工具的使用](other/openssl.md)
    * [sdl2 ffmpeg的编译](other/ffmpeg_install.md)


## C/C++ 小工程/项目
* [练习：随机试卷，做试卷](practice/example-01/summary.md)
* [练习：命令行下的翻译软件](practice/example-02/summary.md)
* [练习：命令行下的贪吃蛇](practice/example-03/summary.md)
* [练习：读取配置文件，配置文件加解密](practice/example-04/summary.md)
* [练习：文件的加解密](practice/example-05/summary.md)
* [练习: 读取文件夹下所有的文件](practice/example-06/summary.md)
* WebServer / HttpClient
* WebRTC / FFmpeg