/**
 * Filename:    fig1-8_testerror.c (Page 12)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 20:23.
 * Description:
 *      strerror 和 perror 函数使用示例
 */
#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[]) {
  // strerror declared in <string.h>: 返回错误代码的字符串表示
  fprintf(stderr, "EACESS: %s\n", strerror(EACCES));
  // perror declared in <stdio.h>: 打印用户提供的消息字符串msg,打印 errno 对应的错误消息err_msg, msg: err_msg\n
  errno = ENOENT;
  perror(argv[0]);
  return 0;
}
