/**
 * Filename: fig5-12_test_tmpxx.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/16/21
 * Description:
 *     tmpnam 和 tmpfile 函数实例
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  char name[L_tmpnam], line[MAXLINE];
  printf("%s\n", tmpnam(NULL)); // first temp name
  tmpnam(name);
  printf("%s\n", name); // second temp name
  FILE *fp;
  if ((fp = tmpfile()) == NULL) {// create temp file
    err_sys("tmpfile error");
  }
  fputs("one line of output\n", fp); // write to temp file
  rewind(fp);
  if (fgets(line, sizeof(line), fp) == NULL) {
    err_sys("fgets error");
  }
  fputs(line, stdout); // print the line we wrote
  return 0;
}

