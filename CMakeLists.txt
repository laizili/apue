cmake_minimum_required(VERSION 3.17)
project(unixprog C)

set(CMAKE_C_STANDARD 99)

# 静态库文件
add_subdirectory(lib)

# 第一章 unix基础知识代码
add_subdirectory(ch1_basic)