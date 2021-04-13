/**
 * Filename: fig4-12_test_chmod.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/11/21
 * Description:
 *     chmod 函数实例，修改文件权限(相对修改与绝对修改)
 */
#include "apue.h"

int main(int argc, char *argv[]) {
  struct stat sb;

  // turn on set-group-id and turn off group-execute for the file 'bar'
  if(stat("bar", &sb) < 0){
    err_sys("stat error for bar");
  }
  if(chmod("bar", (sb.st_mode & ~S_IXGRP) | S_ISGID) < 0){
    err_sys("chmod error for bar");
  }

  // set absolute mode to 'rw-r--r--'
  if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
    err_sys("chmod error for foo");
  }
  return 0;
}

