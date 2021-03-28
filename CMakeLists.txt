cmake_minimum_required(VERSION 3.17)
project(unixprog C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror")
# 静态库文件
add_subdirectory(lib)

# 第一章 unix基础知识代码
add_subdirectory(ch1_unix_system_overview)