/**
 * Filename: fig7_14-problem_automaticvariable.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     使用局部变量的潜在风险
 */

#include <stdio.h>

FILE *open_data() {
  FILE *fp;
  char databuf[BUFSIZ]; // 该对象被分配在栈空间上，当函数返回，该空间（array对象）就会被系统回收，无法继续作为缓冲区使用了；如继续使用，会
  // 破会该进程的栈空间，导致未定义的行为，或严重的运行时错误（编译器检查不出来这种错误）
  if ((fp = fopen("datafile", "wr")) == NULL) {
    return NULL;
  }
  if (setvbuf(fp, databuf, _IOFBF, BUFSIZ) != 0) {
    return NULL;
  }
  return fp;
}

// 不要使用`生命期'结束了数据对象
// open_data函数返回后，databuf对象就被系统回收了，无法作IO缓冲区使用了
int main(int argc, char *argv[]) {

  return 0;
}