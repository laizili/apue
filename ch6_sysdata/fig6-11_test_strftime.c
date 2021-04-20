/**
 * Filename: fig6-11_test_strftime.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/20/21
 * Description:
 * 
 */
#include "apue.h"
#include <time.h>
int main(int argc, char *argv[]) {
  time_t t = time(NULL);
  struct tm *tmptr = localtime(&t);
  char buf1[16];
  char buf2[64];
  if (strftime(buf1, sizeof(buf1), "time and date: %r, %a %b %d, %Y", tmptr) == 0) {
    printf("buffer length %ld is too small\n", sizeof(buf1));
  } else {
    printf("%s\n", buf1);
  }
  if (strftime(buf2, sizeof(buf2), "time and date: %r, %a %b %d, %Y", tmptr) == 0) {
    printf("buffer length %ld is too small\n", sizeof(buf2));
  } else {
    printf("%s\n", buf2);
  }
  return 0;
}