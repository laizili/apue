/**
 * Filename:    fig1-6_getpid.c (Page 9)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 18:13.
 * Description:
 *      打印进程ID
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  printf("hello world from %ld\n", (long) getpid()); // pid_t 类型，标准保证其能保存在一个 long 类型中
  return 0;
}