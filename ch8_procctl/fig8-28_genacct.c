/**
 * Filename: fig8-28_genacct.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/12/21
 * Description:
 *    产生会计数据的程序
 */
#include "apue.h"
int main(int argc, char *argv[]) {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid != 0) { /*parent*/
    sleep(2);
    exit(2);
  }
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid != 0) { /* first child */
    sleep(4);
    abort();
  }
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid != 0) { /* second child */
    execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
    exit(7); // shouldn't get here
  }
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid != 0) { /*third child*/
    sleep(8);
    exit(0);
  }
  sleep(6); // fourth child
  kill(getpid(), SIGKILL); // terminate with signal SIGKILL, no core dump
  exit(6);
  return 0;
}
