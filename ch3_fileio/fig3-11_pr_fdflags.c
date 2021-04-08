/**
 * Filename: fig3-11_pr_fdflags.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/8/21
 * Description:
 *     对于指定的描述符打印文件标志（file status flags）
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    err_quit("usage: %s <descriptor#>", argv[0]);
  }
  pr_file_status_flag(atoi(argv[1]));
  return 0;
}
