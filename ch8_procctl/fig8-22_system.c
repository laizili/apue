/**
 * Filename: fig8-22_system.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/12/21
 * Description:
 *     system（ 函数没有进行信息号处理）
 */
#include "apue.h"
#include <errno.h>
#include <sys/wait.h>

int system(const char *cmdstring);

int main(int argc, char *argv[]) {
  int status;

  if ((status = system("date")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  if ((status = system("nosuchcommand")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  if ((status = system("who;exit 44")) < 0) {
    err_sys("system() error");
  }
  pr_exit(status);

  return 0;
}
int system(const char *cmdstring) { /* version without signal handling */
  if (cmdstring == NULL) {
    return -1;
  }
  int status;
  pid_t pid;
  if ((pid = fork()) < 0) {
    status = -1; // probably out of process
  } else if (pid == 0) {
    execl("/bin/sh", "sh", "-c", cmdstring, NULL);
    _exit(127); // execl error
  } else {
    while (waitpid(pid, &status, 0) < 0) {
      if (errno == EINTR) {
        status = -1;
        break;
      }
    }
  }
  return status;
}
