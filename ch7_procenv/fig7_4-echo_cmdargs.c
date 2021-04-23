/**
 * Filename: fig7_4-echo_cmdargs.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 * 
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  return 0;
}