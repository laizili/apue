/**
 * Filename: fig3-1_lseek_STDIN.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/5/21
 * Description:
 *      测试通过shell打开文件能否被设置偏移量（reposition）
 */
#include "apue.h"
int main(int argc, char *argv[]) {
  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
    fprintf(stderr, "cannot seek\n");
  } else {
    printf("seek OK\n");
  }
  return 0;
}

