/**
 * Filename: fig8-12_proc_with_condition_race.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *    带有竞争条件的程序
 *        父进程打印 a..., 子进程打印 b...
 */

#include "apue.h"

static void charatatime(const char *str);
const char *parent_outstr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"; // 20'a' + '\n'
const char *child_outstr = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"; // 20'b' + '\n'
int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    charatatime(child_outstr);
  } else {
    charatatime(parent_outstr);
  }
  return 0;
}

void charatatime(const char *str) {
  setbuf(stdout, NULL); // set unbuffered
  const char *ptr = str;
  while (*ptr) {
    int c = *ptr++;
    putc(c, stdout);
  }
}