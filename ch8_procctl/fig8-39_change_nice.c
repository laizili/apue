/**
 * Filename: fig8-39_change_nice.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/12/21
 * Description:
 *     更改nice值以影响系统对程序调度优先级，越 nice，进程优先级越低
 */
#include <sys/time.h>
#include <errno.h>
#include "apue.h"

unsigned long long count;

struct timeval et;

void check_time(char *str) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  if (tv.tv_sec >= et.tv_sec && tv.tv_usec >= et.tv_usec) {
    printf("%s count = %lld\n", str, count);
    exit(0);
  }
}

int main(int argc, char *argv[]) {

  int nzero;
  setbuf(stdout, NULL);
#if defined(NZERO)
  nzero = NZERO;
#elif defined(_SC_NZERO)
  nzero = (int) sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
  printf("NZERO = %d\n", nzero);
  int nice_adj = 0;
  if (argc == 2) {
    nice_adj = (int) strtol(argv[1], NULL, 10);
  }
  struct timeval st;
  gettimeofday(&st, NULL);
  et.tv_sec = st.tv_sec + 10; // run for 10 seconds

  pid_t pid;
  char *sid;
  int ret;
  if ((pid = fork()) < 0) {
    err_sys("fork failed");
  } else if (pid == 0) { // child
    sid = "child";
    printf("current nice value in child is %d, adjusting by %d\n", nice(0) + nzero, nice_adj);
    errno = 0;
    if ((ret = nice(nice_adj)) == -1 && errno != 0) {
      err_sys("child set scheduling priority");
    }
    printf("now child nice value is %d\n", ret + nzero);
  } else {
    sid = "parent";
    printf("current nice value in parent is %d\n", nice(0) + nzero);
  }
  while (1) {
    if (++count == 0) {
      err_quit("%s counter wrap", sid);
    }
    check_time(sid);
  }
  return 0;
}