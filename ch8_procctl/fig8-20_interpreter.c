/**
 * Filename: fig8-20_interpreter.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/4/21
 * Description:
 *    执行一个解释器文件（脚本文件）的程序
 */

#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { // child
    if (execl("/tmp/testinterp", "testinterp", "myarg1", "MY ARG2", NULL) < 0) {
      err_sys("exec error");
    }
  }
  // parent
  if (waitpid(pid, NULL, 0) != pid) {
    err_sys("waitpid error");
  }
  return 0;
}