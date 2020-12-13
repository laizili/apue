/**
 * Filename:    fig1-4_mycat.c (Page 7)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/11 T 16:30.
 * Description:
 *     将标准输入复制到标准输出
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  char buf[MAXLINE];
  int rn = 0; // 读取的字符个数
  while ((rn = read(STDIN_FILENO, buf, MAXLINE)) > 0) {
    if (write(STDOUT_FILENO, buf, rn) != rn) {
      err_sys("write error");
    }
  }
  if (rn < 0) {
    err_sys("read error");
  }
  return 0;
}
