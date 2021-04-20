/**
 * Filename: print_sysinfo.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/20/21
 * Description:
 * 
 */

#include "apue.h"
#include <sys/utsname.h>

int main(int argc, char *argv[]) {
  struct utsname sysinfo;
  if (uname(&sysinfo) < 0) {
    err_sys("get system information error");
  }
  printf("os: %s\n", sysinfo.sysname);
  printf("node: %s\n", sysinfo.nodename);  // 网络中节点名称
  printf("kernel: %s\n", sysinfo.release); // 内核版本号
  printf("version: %s\n", sysinfo.version); //内核发行版本号
  printf("arch: %s\n", sysinfo.machine);   // 硬件结构
  return 0;
}