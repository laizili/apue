/**
 * Filename: fig5-11_pr_stdio_info.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/15/21
 * Description:
 *     对各个标准I/O流打印缓冲状态信息
 */

#include "apue.h"
#include <stdio_ext.h>
void pr_stdio(const char *name, FILE *fp);
int is_unbuffered(FILE *fp);
int is_linebuffered(FILE *fp);
long buffer_size(FILE *fp);

int main(int argc, char *argv[]) {
  fputs("enter any character\n", stdout);
  if (getchar() == EOF) {
    err_sys("getchar error");
  }
  fputs("one line to standard error\n", stderr);
  pr_stdio("stdin", stdin);
  pr_stdio("stdout", stdout);
  pr_stdio("stderr", stderr);

  FILE *fp;
  if ((fp = fopen("/etc/passwd", "r")) == NULL) {
    err_sys("fopen error");
  }
  if (getc(fp) == EOF) {
    err_sys("getc error");
  }
  pr_stdio("/etc/passwd", fp);
  return 0;
}

void pr_stdio(const char *name, FILE *fp) {
  printf("stream = %s, ", name);
  if (is_unbuffered(fp)) {
    printf("unbuffered");
  } else if (is_linebuffered(fp)) {
    printf("line buffered");
  } else {
    printf("full buffered");
  }
  printf(", buffer size = %ld\n", buffer_size(fp));
}

//TODO: non-portable: look up struct `FILE' in your system for more details
int is_unbuffered(FILE *fp) {
  return buffer_size(fp) == 1; //从缓冲区的外在表现出发(输入即刻输出)，判断缓冲类型
}
int is_linebuffered(FILE *fp) {
  return __flbf(fp) != 0;
}
long buffer_size(FILE *fp) {
  return __fbufsize(fp);
}

