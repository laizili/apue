/**
 * Filename: fig7-13_longjump_effects.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     longjmp对各类变量的影响（自动变量、全局变量、寄存器变量、静态变量、易失变量）
 */

#include "apue.h"
#include <setjmp.h>

static jmp_buf jmpbuffer;
static int globval = 1; // 全局变量

static void f1(int, int, int, int);
static void f2();
/*
 * excerpt from `setjmp(3)':
 *     The  compiler may optimize variables into registers, and longjmp() may restore
 *     the values of other registers in addition to the  stack  pointer  and  program
 *     counter.   Consequently, the values of automatic variables are unspecified af‐
 *     ter a call to longjmp() if they meet all the following criteria:
 *
 *     •  they are local to the function that made the corresponding setjmp() call;
 *
 *     •  their values are changed between the calls to setjmp() and longjmp(); and
 *
 *     •  they are not declared as volatile.
 * 解释：
 *     函数体内非静态局部变量，经编译器优化后，其存储位置可能在cpu的某个寄存器中，会导致setjmp调用后对这些变量的修改在
 *     longjmp后值回到setjmp前的状态，若要保留这些更改，需要对其进行volatile声明
 */
int main(int argc, char *argv[]) {
  int autoval = 2; // 自动变量
  register int regival = 3; // 寄存器变量
  volatile int volaval = 4; // 易失变量
  static int statval = 5; // 静态变量
  if (setjmp(jmpbuffer) != 0) {
    printf("after longjmp:\n");
    printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
           globval,
           autoval,
           regival,
           volaval,
           statval);
    exit(0);
  }
  /* change variables after setjmp, but before longjmp */
  globval = 95;
  autoval = 96;
  regival = 97;
  volaval = 98;
  statval = 99;
  f1(autoval, regival, volaval, statval);
  return 0;
}

void f1(int av, int rv, int vv, int sv) {
  printf("in f1():\n");

  printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
         globval,
         av,
         rv,
         vv,
         sv);
  f2();
}
void f2() {
  longjmp(jmpbuffer, 1);
}