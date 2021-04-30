/**
 * Filename: fig7-4_echo_cmdargs.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     打印所有命令行参数
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  return 0;
}