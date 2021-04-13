/**
 * Filename: fig4-23_test_chdir.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/12/21
 * Description:
 *     调用chdir函数改变当前进程的工作目录
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  if(chdir("/tmp") < 0){
    err_sys("chdir error");
  }
  printf("chdir to /tmp succeed\n");
  return 0;
}