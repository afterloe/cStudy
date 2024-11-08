libevent 网络工具库
===

## 安装
```
wget https://objects.githubusercontent.com/libevent-2.1.12-stable.tar.gz -o libevent-2.1.12-stable.tar.gz
tar -xzvf libevent-2.1.12-stable.tar.gz -C /usr/local/src
cd /usr/local/src

sudo apt install libssl-dev
sudo apt install libssl-doc

sudo ./configure
sudo make
sudo make install
```

## 使用
头文件目录: `/usr/local/include`   
库路径: `/usr/local/lib`