/**
 * Filename: test_memstream.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/16/21
 * Description:
 * 
 */
#include "apue.h"
struct Person {
  char name[32];
  int age;
};

// 用内存流 读写二进制数据
int main(int argc, char *argv[]) {
  struct Person p[] = {{"李东晖", 23}, {"来自立", 32}};
  char buf[BUFSIZ];
  FILE *fp = fmemopen(buf, BUFSIZ, "w+");
  fwrite(p, sizeof(struct Person), 2, fp);
  fflush(fp);
  // 把写入fp的结构提person数据刷入 buf
  struct Person *np = (struct Person *) buf;
  for (int i = 0; i < 2; ++i) { // 打印缓冲区的内容
    printf("%s %d\n", np[i].name, np[i].age);
  }
  printf("=======================");
  // fread 读入写入的数据
  rewind(fp);
  struct Person ps[2];
  fread(ps, sizeof(struct Person), 2, fp);
  for (int i = 0; i < 2; ++i) { // 打印读出的内容
    printf("%s %d\n", ps[i].name, ps[i].age);
  }
  return 0;
}