/**
 * Filename: fig7-16_pr_rlimits.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     获取并打印进程的当前资源限制
 */
#include "apue.h"
#include "sys/resource.h"

#define doit(name) pr_rlimits(#name, name)
static void pr_rlimits(const char *rname, int rtype);

int main(int argc, char *argv[]) {
  printf("%-24s\t%10s\t%10s\n", "resource name", "soft-limit", "hard-limit");
#ifdef RLIMIT_AS
  doit(RLIMIT_AS);
#endif

  doit(RLIMIT_CORE);
  doit(RLIMIT_CPU);
  doit(RLIMIT_DATA);
  doit(RLIMIT_FSIZE);

#ifdef RLIMIT_MEMLOCK
  doit(RLIMIT_MEMLOCK);
#endif
#ifdef RLIMIT_MSGQUEUE
  doit(RLIMIT_MSGQUEUE);
#endif
#ifdef RLIMIT_NICE
  doit(RLIMIT_NICE);
#endif

  doit(RLIMIT_NOFILE);

#ifdef RLIMIT_NPROC
  doit(RLIMIT_NPROC);
#endif
#ifdef RLIMIT_NPTS
  doit(RLIMIT_NPTS);
#endif
#ifdef RLIMIT_RSS
  doit(RLIMIT_RSS);
#endif
#ifdef RLIMIT_SBSIZE
  doit(RLIMIT_SBSIZE);
#endif
#ifdef RLIMIT_SIGPENDING
  doit(RLIMIT_SIGPENDING);
#endif

  doit(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
  doit(RLIMIT_SWAP);
#endif
#ifdef RLIMIT_VMEM
  doit(RLIMIT_VMEM);
#endif
  return 0;
}

void pr_rlimits(const char *rname, int rtype) {
  struct rlimit rlimittmp;

  if (getrlimit(rtype, &rlimittmp) < 0) {
    err_sys("getrlimit error for %s", rname);
  }
  printf("%-24s\t", rname);
  if (rlimittmp.rlim_cur == RLIM_INFINITY) {
    printf("%10s\t", "(infinite) ");
  } else {
    printf("%10lu\t", rlimittmp.rlim_cur);
  }
  if (rlimittmp.rlim_cur == RLIM_INFINITY) {
    printf("%10s", "(infinite) ");
  } else {
    printf("%10lu ", rlimittmp.rlim_cur);
  }
  printf("\n");
}
