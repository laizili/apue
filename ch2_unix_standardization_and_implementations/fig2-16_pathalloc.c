//
// Created by laizili on 1/20/21.
//
// 为路径名动态分配存储区

#include "apue.h"
#include <errno.h>
#include <limits.h>

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

// test driver
int main(int argc, char *argv[]) {
  size_t pathbuf_len = 0; // 路径缓冲区长度
  char *ppathbuf = path_alloc(&pathbuf_len); // 指向路径缓冲区的指針

  // 获取进程的工作目录
  getcwd(ppathbuf, pathbuf_len);
  printf("current working directory is \"%s\"\n", ppathbuf);

  free(ppathbuf); // 手动释放在堆空间上分配内存，避免內存泄露
  return 0;
}