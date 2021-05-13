/**
 * Filename: tell_wait.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/30/21
 * Description:
 *    用信号实现父子进程之间的同步，这是信号应用的另一个实例
 *    TELLWAIT、WAIT_PARENT、TELL_PARENT、WAIT_CHILD、TELL_CHILD
 */
#include "apue.h"
#include <signal.h>

static volatile sig_atomic_t sigflag; // set non-zero by sig handler
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) { // one signal handler for SIGUSR1 and SIGUSR2
  sigflag = 1;
}

// 建立对SIGUSR1和SIGUSR2d的信号处理和信号屏蔽字
void TELLWAIT() {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    err_sys("signal(SIGUSR1) error");
  }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    err_sys("signal(SIGUSR2) error");
  }
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);
  // block SIGUSR1/SIGUSR2, and save current signal mask
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
    err_sys("SIG_BLOCK error");
  }
}

void TELL_PARENT(pid_t pid) {
  kill(pid, SIGUSR2); // tell parent we're done
}

void WAIT_PARENT() {
  while (sigflag == 0) {
    sigsuspend(&zeromask); // wait for parent
  }
  sigflag = 0;
  // reset signal mask to original value
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }
}

void TELL_CHILD(pid_t pid) {
  kill(pid, SIGUSR1); // tell child we're done
}

void WAIT_CHILD() {
  while (sigflag == 0) {
    sigsuspend(&zeromask); // wait for child
  }
  sigflag = 0;
  // reset signal mask to  original value
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err_sys("SIG_SETMASK error");
  }
}