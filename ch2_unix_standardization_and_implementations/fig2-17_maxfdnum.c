/**
 * Filename: fig_2-17_maxfdnum.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     3/26/21
 * Description:
 *      确定进程可以同时打开的文件描述符的最大个数
 */

#include "apue.h"

//说明： 将open_max 函数定义转移到 lib/open_max.c 文件中，open_max 是libapue.a库的组件

//test for function `open_max'
int main(int argc, char *argv[]) {
  long ret = open_max();
  printf("%s can open maximum \"%ld\"  file descriptor\n", argv[0], ret); // LONG_MAX 意味着 无限制（unlimited)
  return 0;
}

