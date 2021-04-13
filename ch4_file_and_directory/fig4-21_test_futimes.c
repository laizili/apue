/**
 * Filename: fig4-21_test_futimes.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/12/21
 * Description:
 *     截断文件，但不修改文件的最后访问和修改时间
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  int fd;
  struct stat sb;
  struct timespec ts[2];
  for (int i = 1; i < argc; ++i) {
    if (stat(argv[i], &sb) < 0) {  // fetch current times
      err_ret("%s: stat error", argv[i]);
      continue;
    }
    if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { // truncate file
      err_ret("%s: open error", argv[i]);
      continue;
    }
    ts[0] = sb.st_atim;
    ts[1] = sb.st_mtim;
    if (futimens(fd, ts) < 0) {   // reset times
      err_ret("%s: futimes error", argv[i]);
    }
    close(fd);
  }
  return 0;
}