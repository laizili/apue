/**
 * Filename: path_alloc.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/8/21
 * Description:
 *   为路径名动态分配存储区
 */

#include "apue.h"
#include <errno.h>

#ifdef PAHT_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;
#define PATH_MAX_GUESS 1024  // 假定PATH_MAX的大小

char *path_alloc(size_t *sizep) {/*alse return allocated size, if nonnull*/
  if (posix_version == 0) {
    posix_version = sysconf(_SC_VERSION);
  }
  if (xsi_version == 0) {
    xsi_version = sysconf(_SC_XOPEN_VERSION);
  }

  if (pathmax == 0) {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0) {
        pathmax = PATH_MAX_GUESS;
      } else {
        err_sys("pathconf error for _PC_PATH_MAX");
      }
    } else {
      ++pathmax; // 增加一个字节，因为相对于根目录/
    }
  }
  size_t size = 0;
  if (posix_version < 200112L && xsi_version < 4) {
    size = pathmax + 1;
  } else {
    size = pathmax;
  }
  char *retp = NULL;
  if ((retp = malloc(size)) == NULL) {
    err_sys("malloc error for pathname");
  }
  if (sizep != NULL)
    *sizep = size; // 将分配的空间长度写出到输出参数sizep所指的对象中
  return retp;
}
