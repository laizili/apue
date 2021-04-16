/**
 * Filename: fig5-4_mycat2.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/15/21
 * Description:
 *     用getch和putc将标准输入复制到标准输出
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  int chr;
  while ((chr = fgetc(stdin)) != EOF) {
    if (fputc(chr, stdout) == EOF) {
      err_sys("output error");
    }
  }
  if (ferror(stdin)) {
    err_sys("input error");
  }
  return 0;
}

