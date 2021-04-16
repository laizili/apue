/**
 * Filename: fig5-15_examine_memstream.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/16/21
 * Description:
 *     观察内存流的写入操作
 */

#include "apue.h"
#define BSZ 48

int main(int argc, char *argv[]) {
  char buf[BSZ];
  memset(buf, 'a', BSZ - 2);
  buf[BSZ - 1] = '\0';
  buf[BSZ - 2] = 'X';
  FILE *fp;
  if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) {
    err_sys("fmemopen failed");
  }
  printf("initial buffer contents: %s\n", buf);
  fprintf(fp, "hello, world");
  printf("before fflush: %s\n", buf);
  fflush(fp);
  printf("after fflush: %s\n", buf);
  printf("len of strin in buf = %ld\n", (long) strlen(buf));

  memset(buf, 'b', BSZ - 2);
  buf[BSZ - 1] = '\0';
  buf[BSZ - 2] = 'X';
  fprintf(fp, "hello, world");
  fseek(fp, 0, SEEK_CUR);
  printf("after fseek:%s\n", buf);
  printf("len of string in buf = %ld\n", (long) strlen(buf));

  memset(buf, 'c', BSZ - 2);
  buf[BSZ - 1] = '\0';
  buf[BSZ - 2] = 'X';
  fprintf(fp, "hello, world");
  fclose(fp);
  printf("after fclose: %s\n", buf);
  printf("len of string in buf = %ld\n", (long) strlen(buf));
  return 0;
}
