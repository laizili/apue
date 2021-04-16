/**
 * Filename: fig5-5_mycat3.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/15/21
 * Description:
 *     用fgets和fputs将标准输入复制到标准输出
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  char buf[MAXLINE];

  while (fgets(buf, sizeof(buf), stdin) != NULL){
    if(fputs(buf, stdout) == EOF){
      err_sys("output error");
    }
  }
  if(ferror(stdin)){
    err_sys("input error");
  }
  return 0;
}