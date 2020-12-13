/**
 * Filename:    test.c
 * Author:      csbonkers
 * Contact:     csbonkers@mail.ynu.edu.cn 
 * Date:        2020/12/12 T 20:17.
 * Description:
 *
 */
#include "apue.h"
int main(int argc, char *argv[]) {
  int n;
  while (scanf("%d", &n) != EOF){
    printf("%s\n", strerror(n));
  }

  return 0;
}

