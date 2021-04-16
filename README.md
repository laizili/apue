**Platform Environment:**

    1. OS: WIN10
    2. IDE: CLION
    3. Toolchains: cygwin
    4. CMAKE 3.17
    5. Python 3.x.x

[toc]

### APUE.3E 书籍源码

#### lib目录, 各章文件依赖的静态库文件(libapue.a)

#### 1. ch1_basic 第一章 UNIX基础知识

> UNIX系统概览

#### 2. ch2_standards 第二章 UNIX标准及实现

> 介绍了 C语言标准、UNIX标准 及 不同OS厂商对标准实现差异等

#### 3. ch3_fileio 第三章 文件IO

> 1. 介绍了文件的打开、读取、写入、关闭及与文件描述符操作相关的函数(`open/read/write/close/fcntl`)；
>
>2. 文件同步函数(`sync/fsync/fdatasync`)，将写到内存缓冲区的内容同步到磁盘中.

#### 4. ch4_file_and_directory

> 1. 围绕stat函数，介绍了`struct stat`结构的各个字段含义，如文件类型、文件访问权限、文件时间戳等；介绍了umask 及各种文件和目录相关的操
> 作函数；介绍了硬链接与软连接的概念及相关操作函数;
> 
>2. 介绍了进程属性(`当前工作目录`)的概念，获取及更改进程当前工作目录的相关函数.

#### 5. ch5_fileio
> 1. 介绍了操作`FILE *`(stdio stream)相关函数(打开、读写、定位、冲洗、关闭)，以及设置流缓冲的函数;
> 
> 2. 还介绍了内存流与临时文件相关的标准IO库提供的函数等
