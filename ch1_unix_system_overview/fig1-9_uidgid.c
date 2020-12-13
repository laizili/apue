/**
 * Filename:    fig1-9_uidgid.c (Page 14)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 21:20.
 * Description:
 *      打印用户ID和组ID
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  printf("uid = %d, gid = %d\n", getuid(), getgid());// uid_t gid_t
  return 0;
}