/**
 * Filename: open_max.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/8/21
 * Description:
 *     进程可以打开最大打开文件数
 */

#include "apue.h"
#include <errno.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
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
