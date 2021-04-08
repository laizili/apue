/**
 * Filename: fig3-5_mycat.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/5/21
 * Description:
 *      将标准输入复制到标准输出（在shell中运行本程序，通过shell输入输出重定向实现文件拷贝）
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  char buf[BUFSIZ];
  int n; // 读入的char(byte)个数
  while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
    if (write(STDOUT_FILENO, buf, n) != n) {
      err_sys("writer error");
    }
  }
  if (n < 0) {
    err_sys("read error");
  }
  return 0;
}

