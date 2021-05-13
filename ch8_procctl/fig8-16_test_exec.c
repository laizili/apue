/**
 * Filename: fig8-16_test_exec.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *     演示exec函数族的使用方法
 */

#include "apue.h"
#include <sys/wait.h>
// new environment list
const char *env_list[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) { // specify pathname, specify environment
    if (execle("/tmp/fig8-17_echoall", "fig8-17_echoall", "myarg1", "MY ARG2", NULL, env_list) < 0) {
      err_sys("execle error");
    }
  }
  if (waitpid(pid, NULL, 0) < 0) {
    err_sys("fork error");
  }

  // 将 /tmp 添加到环境变量中
  const char *path = getenv("PATH");
  char buf[BUFSIZ];
  strncpy(buf, path, sizeof(buf));
  const char new_path_component[] = ":/tmp";
  strncat(buf, new_path_component, strlen(new_path_component) + 1);
  setenv("PATH", buf, 1);

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    if (execlp("fig8-17_echoall", "echoall", "only 1 arg", NULL) < 0) {
      err_sys("execlp error");
    }
  }
  waitpid(0, NULL, 0); // wait child to exit
  return 0;
}

