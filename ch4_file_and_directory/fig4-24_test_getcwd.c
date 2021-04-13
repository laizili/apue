/**
 * Filename: fig4-24_test_getcwd.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/12/21
 * Description:
 * 
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  if (chdir("/lib") < 0) { // change process's working directory
    err_sys("chdir failed");
  }
  size_t sz;
  char *pathbuf = path_alloc(&sz);
  if (getcwd(pathbuf, sz) < 0) { // get current working directory
    err_sys("getcwd failed");
  }
  printf("cwd = %s\n", pathbuf);
  free(pathbuf);
  return 0;
}