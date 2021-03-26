cmake_minimum_required(VERSION 3.16)
project(unixprog C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall")
# 静态库文件
add_subdirectory(lib)
# 测试
add_executable(test test.c)
target_link_libraries(test apue)

# 第一章 unix基础知识代码
add_subdirectory(ch1_unix_system_overview)
# 第二章 unix标准及实现
add_subdirectory(ch2_standards)

add_subdirectory(ch3_fileio)