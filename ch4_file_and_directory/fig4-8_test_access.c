#include "apue.h"

/**
 * Filename: fig4-8_test_access.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/9/21
 * Description:
 *    access 函数使用实例
 */
int main(int argc, char *argv[]) {
  if (argc != 2) {
    err_quit("usage: %s <pathname>", argv[0]);
  }
  if (access(argv[1], R_OK) < 0) { // real user test read permission
    err_ret("access error for %s", argv[1]);
  } else {
    printf("read access OK\n");
  }

  if (open(argv[1], O_RDONLY) < 0) { // effective user test read permission
    err_ret("open error for %s", argv[1]);
  } else {
    printf("open for reading ok\n");
  }
  // 通过 faccessat 以实际用户身份测试相应文件权限位
  /*if (faccessat(AT_FDCWD, argv[1], R_OK, AT_EACCESS) < 0) { // effective user test read permission
    err_ret("faccessat error for %s", argv[1]);
  } else {
    printf("read access ok\n");
  }*/

  return 0;
}