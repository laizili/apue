/**
 * Filename: fig4-25_pr_devt.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/13/21
 * Description:
 *      打印 st_dev 和st_rdev值
 */
#include "apue.h"
#include <sys/sysmacros.h>
int main(int argc, char *argv[]) {
  struct stat sb;
  for (int i = 1; i < argc; ++i) {
    printf("%s: ", argv[i]);
    if (stat(argv[i], &sb) < 0) {
      err_ret("stat error");
      continue;
    }
    printf("dev = %d/%d", major(sb.st_dev), minor(sb.st_dev));
    if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode)) {
      printf(" (%s)rdev %d/%d", S_ISCHR(sb.st_mode) ? "character" : "block", major(sb.st_rdev),
             minor(sb.st_rdev));
    }
    putchar('\n');
  }
  return 0;
}