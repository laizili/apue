/**
 * Filename:    fig1-5_getcputc.c (Page 8)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 11:30.
 * Description:
 *      用标准IO将标准输入复制到标准输出
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  int c;
  while ((c = getc(stdin)) != EOF) {
    if (putc(c, stdout) == EOF) {
      err_sys("output error");
    }
  }
  if (ferror(stdin)) {
    err_sys("input error");
  }
  return 0;
}
