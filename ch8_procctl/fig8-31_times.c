/**
 * Filename: fig8-31_times.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/12/21
 * Description:
 *      获取进程运行时间
 *      get process times
 */
#include "apue.h"
#include <sys/times.h>

static void pr_times(clock_t real, const struct tms *tms_st, const struct tms *tms_et);
static void do_cmd(char *cmd);
int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  for (int i = 1; i < argc; ++i) {
    do_cmd(argv[i]); // once for each command-line arg.
  }
  return 0;
}

void do_cmd(char *cmd) {
  struct tms tms_st, tms_et;
  clock_t st, et;
  if ((st = times(&tms_st)) == -1) { // staring
    err_sys("times error");
  }
  int status;
  if ((status = system(cmd)) < 0) { // executing
    err_sys("system() error");
  }
  if ((et = times(&tms_et)) == -1) {
    err_sys("times error");
  }
  pr_times(et - st, &tms_st, &tms_et);
  pr_exit(status);
  printf("\n");
}
void pr_times(clock_t real, const struct tms *tms_st, const struct tms *tms_et) {
  static long clktck = 0;
  if (clktck == 0) {
    if ((clktck = sysconf(_SC_CLK_TCK)) < 0) { // fetch clock ticks per second first time
      err_sys("sysconf error");
    }
  }
  printf("  real:  %7.2f\n", real / (double) clktck);
  printf("  user:  %7.2f\n", (tms_et->tms_utime - tms_st->tms_utime) / (double) clktck);
  printf("  sys: %7.2f\n", (tms_et->tms_stime - tms_st->tms_stime) / (double) clktck);
  printf("  child user:  %7.2f\n", (tms_et->tms_cutime - tms_st->tms_cutime) / (double) clktck);
  printf("  child sys: %7.2f\n", (tms_et->tms_cstime - tms_st->tms_cstime) / (double) clktck);
}
