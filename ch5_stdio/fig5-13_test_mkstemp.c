/**
 * Filename: fig5-13_test_mkstemp.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/16/21
 * Description:
 *     mkstemp 函数的应用
 */

#include <errno.h>
#include "apue.h"

void make_temp(char *template);
int main(int argc, char *argv[]) {
  char good_template[] = "/tmp/dirXXXXXX"; // right way
  char *bad_template = "/tmp/dirXXXXXX"; // bad way, XXXXXX字符串会被原地替换，常量区字符串无法修改，否则造成段错误
  printf("trying to create first temp file...\n");
  mkstemp(good_template);
  printf("trying to create second temp file...\n");
  make_temp(bad_template); // cause `segmentation fault'
  return 0;
}

void make_temp(char *template) {
  int fd;
  if ((fd = mkstemp(template)) < 0) {
    err_sys("can't create temp file");
  }
  printf("temp name = %s\n", template);
  close(fd);

  struct stat sb;
  if (stat(template, &sb) < 0) {
    if (errno == ENOENT) {
      printf("file doesn't exist");
    } else {
      err_sys("stat failed");
    }
  } else {
    printf("file exists\n");
    unlink(template); // mkstemp 创建的文件不会被自动删除，需要调用这手动删除该文件
  }
}
