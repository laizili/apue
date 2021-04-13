/**
 * Filename: fig4-16_open_unlink.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/12/21
 * Description:
 *     打开一个文件，然后解除对它的链接，执行执行该程序的进程休眠15秒，接着就终止
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  const char *filename = "tmpfile";
  if (open(filename, O_RDWR | O_CREAT) < 0) {
    err_sys("open error for file tmpfile");
  }
  if (unlink(filename) < 0) {
    err_sys("unlink error");
  }
  printf("file unlinked\n");
  sleep(15);
  printf("done");
  return 0;
}