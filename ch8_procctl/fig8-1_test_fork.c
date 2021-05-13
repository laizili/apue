/**
 * Filename: fig8-1_test_fork.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *     fork 函数示例
 */

#include "apue.h"

int globvar = 6; /*external variable in initialized data*/
char buf[] = "a write to stdout\n";

int main(int argc, char *argv[]) {
  int var = 88; /*automatic variable on the stack*/
  if(write(STDOUT_FILENO, buf, sizeof(buf) -1) != sizeof(buf) -1){
    err_sys("write error");
  }
  printf("before fork\n"); /*we don't flush stdout*/
  pid_t pid;
  if((pid=fork()) <0){
    err_sys("fork error");
  }else if(pid==0){ /* child */
    globvar++;  /* modify variables */
    var++;
  }else{ /* parent */
    sleep(2);
  }
  // after fork: code which both child and parent pass though
  printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
  return 0;
}

