/**
 * Filename: fig_2-17_maxfdnum.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     3/26/21
 * Description:
 *      确定进程可以同时打开的文件描述符的最大个数
 */

#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256  // 假定此进程可以同时打开的最大文件描述符数量为256

long open_max() {
  errno = 0;
  if (openmax == 0) {
    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
      if (errno != 0) {
        err_sys("sysconf error for _SC_OPEN_MAX");
      } else {
        openmax = OPEN_MAX_GUESS;
      }
    }
  }
  return openmax;
}

int main(int argc, char *argv[]) {
  long ret = open_max();
  printf("%s can open maximum \"%ld\"  file descriptor\n", argv[0], ret); // LONG_MAX 意味着 无限制（unlimited)
  return 0;
}

