/**
 * Filename:    fig1-10_shell2.c (Page 15)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 21:36.
 * Description:
 *      基本shell实例基础上，添加对 SIGINT 信号的处理功能
 */
#include "apue.h"
#include <sys/wait.h>

typedef unsigned long ulong_t; // 类型别名 ulong_t
static void sig_int(int signo); // our own signal-catching function

int main(int argc, char *argv[]) {
  if (signal(SIGINT, sig_int) == SIG_ERR) { // install our own signal-catching function handler
    err_sys("signal error");
  }
  printf("%% "); // print command prompt %
  char buf[MAXLINE];
  pid_t pid;
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    ulong_t rn = strlen(buf);
    if (buf[rn - 1] == '\n') {
      buf[rn - 1] = '\0'; // 命令以nul字符结尾
    }
    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) { // child process
      execlp(buf, buf, NULL);
      err_ret("can't execute %s", buf);
      exit(127); // child process terminate
    }
    // parent process: wait for child process to terminate and then print prompt
    if ((pid = waitpid(pid, NULL, 0)) < 0) {
      err_sys("wait_pid error");
    }
    printf("%% ");
  }
  return 0;
}

void sig_int(int signo) {
  printf("interrupt\n%% ");
}