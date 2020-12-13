/**
 * Filename:    fig1-7_shell1.c (Page 9)
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 18:21.
 * Description:
 *      基本shell实例，从标准输入读取命令，派生(spawn: fork + exec)子进程执行该命令,父进程调用waitpid
 *   等待子进程执行结束
 *   Ctrl + D  ^D 文件结束符
 *
 */
#include "apue.h"
#include <sys/wait.h>

typedef unsigned long ulong_t; // 类型别名 ulong_t

int main(int argc, char *argv[]) {
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

