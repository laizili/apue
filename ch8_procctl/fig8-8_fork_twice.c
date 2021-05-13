/**
 * Filename: fig8-8_fork_twice.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *    如果一个进程fork两个子进程，但不要等待子进程终止，同时不希望子进程结束后处于僵死状态，可以通过fork两次实现
 */

#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { // first child
    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid > 0) {
      exit(0); // first child exit immediately
    }

    /*  we're the second child; our parent becomes init as soon as our real parent call exit() int the statement above.
     *  Here's where we'd continue executing, knowing that when we're done, init will reap our status.
     */

    // do something else
    sleep(2);
    printf("second child, parent pid = %ld\n", (long) getppid());
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid) {
    err_sys("waitpid error");
  }
  //do something else
  /*
   * we're the parent(the orginal process); we continue executing,
   * knowing that we're not the parent of the second child.
   */
  return 0;
}
