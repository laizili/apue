/**
 * Filename: fig8-6_show_exitstatus.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *     演示不同的exit值
 */

#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int status;

  if((pid = fork()) < 0){
    err_sys("fork error");
  }else if(pid == 0){ /* child */
    exit(7);
  }
  if(wait(&status) != pid){ /* wait for child*/
    err_sys("wait error");
  }
  pr_exit(status); /* and print its status */

  if((pid = fork()) < 0){
    err_sys("fork error");
  } else if(pid == 0){ /* child generate SIGABRT */
    abort();
  }
  if(wait(&status) != pid){
    err_sys("wait error");
  }
  pr_exit(status);

  if((pid=fork()) < 0){
    err_sys("fork error");
  }else if(pid == 0){ /*child: divide by 0 generates SIGFPE*/
    int c = 0;
    status /= c;
  }
  if(wait(&status)!=pid){
    err_sys("wait error");
  }
  pr_exit(status);

  return 0;
}
