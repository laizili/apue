/**
 * Filename: fig8-17_echoall.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *     回显所有命令行参数和所有环境字符串
 */

#include "apue.h"
extern char **environ;

// 参数表和环境表都是以 `NULL结尾的char*数组'（type: char *(args/argv)[]）
int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d]: %s\n", i, argv[i]); // echo all command-line args
  }
  char **p_string = environ;
  while (*p_string) { // echo all env strings
    printf("%s\n", *p_string++);

  }
  return 0;
}
