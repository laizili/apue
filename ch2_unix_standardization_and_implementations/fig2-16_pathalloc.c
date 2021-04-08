//
// Created by laizili on 1/20/21.
//
// 为路径名动态分配存储区

#include "apue.h"

//说明： path_alloc 函数定义转移到 lib/path_alloc.c文件中，这个函数是静态库 libapue.a 的一部分

// test for function `path_alloc'
int main(int argc, char *argv[]) {
  size_t pathbuf_len = 0; // 路径缓冲区长度
  char *ppathbuf = path_alloc(&pathbuf_len); // 指向路径缓冲区的指針

  // 获取进程当前工作目录
  getcwd(ppathbuf, pathbuf_len);
  printf("current working directory is \"%s\"\n", ppathbuf);

  free(ppathbuf); // 手动释放在堆空间上分配内存，避免內存泄露
  return 0;
}