/**
 * Filename: umask.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/9/21
 * Description:
 *     umask 函数使用实例
 */
#include "apue.h"
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) // 用户、组、其他用户具有读写权限
#define __RWRW (S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) // 屏蔽新创建的文件的组用户其他用户读写权限位
int main(int argc, char *argv[]) {
  umask(0);
  if (creat("bar", RWRWRW) < 0) {
    err_sys("creat error for bar");
  }
//  umask(0066);
  umask(__RWRW);
  if (creat("foo", RWRWRW) < 0) {
    err_sys("creat error for foo");
  }
  return 0;
}