cmake_minimum_required(VERSION 3.16)
project(unixprog C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror")
# 静态库文件
add_subdirectory(lib)

# 第一章 unix基础知识代码
add_subdirectory(ch1_unix_system_overview)
# 第二章 unix标准及实现
add_subdirectory(ch2_unix_standardization_and_implementations)
# 第三章 文件IO
add_subdirectory(ch3_fileio)
# 第四章 文件和目录
add_subdirectory(ch4_file_and_directory)
# 第五章 标准I/O库
add_subdirectory(ch5_stdio)
# 第六章 系统数据文件和信息
add_subdirectory(ch6_sysdata)
# 第七章 进程环境
add_subdirectory(ch7_procenv)
# 第八章 进程控制
add_subdirectory(ch8_procctl)