/**
 * Filename: ch7-3_test_atexit.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     使用atexit 注册进程正常终止处理程序
 */
#include"apue.h"

static void my_exit1();
static void my_exit2();
int main(int argc, char *argv[]) {
  if (atexit(my_exit2) != 0) {
    err_sys("can't register my_exit2");
  }
  if (atexit(my_exit1) != 0) {
    err_sys("can't register my_exit1");
  }
  if (atexit(my_exit1) != 0) {
    err_sys("can't register my_exit1");
  }
  printf("main is done\n");
  return 0;
}

void my_exit1() {
  printf("first exit handler\n");
}

void my_exit2() {
  printf("second exit handler\n");
}

