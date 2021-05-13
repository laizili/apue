/**
 * Filename: fig8-13_proc_avoid_race_condition.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *     同步父子进程，避免父子进程的竞争条件
 */

#include "apue.h"

static void charatatime(const char *str);
const char *parent_outstr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"; // 20'a' + '\n'
const char *child_outstr = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n"; // 20'b' + '\n'
int main(int argc, char *argv[]) {
  TELLWAIT();
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    WAIT_PARENT(); // parent goes first
    charatatime(child_outstr);
  } else {
    charatatime(parent_outstr);
    TELL_CHILD(pid); // wake up child
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