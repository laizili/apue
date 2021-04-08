/**
 * Filename: fig3-12_file_flags.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/8/21
 * Description:
 *      对一个文件描述符开启一个或多个文件状态标志
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  int fdg = fcntl(STDIN_FILENO, F_GETFD);
  printf("==============================\n");
  printf("设置close_on_exec文件描述符标志\n");
  printf("设置前: %d\n", fdg);
  set_cloexec(STDIN_FILENO);
  fdg = fcntl(STDIN_FILENO, F_GETFD);
  printf("设置后: %d\n", fdg);

  /*
   * 说明：
   *     On  Linux,  this  command can change only the O_APPEND, O_ASYNC,O_DIRECT, O_NOATIME, and O_NONBLOCK flags.
   *  It is  not  possible to change the O_DSYNC and O_SYNC flags.
   *
   */
  printf("==============================\n");
  printf("打开`O_NONBLOCK'标志位前`STDIN_FILENO'的文件状态标志为:\n\t");
  pr_file_status_flag(STDIN_FILENO);

  printf("打开`O_NONBLOCK'标志位后`STDIN_FILENO'的文件状态标志为:\n\t");
  set_fl(STDIN_FILENO, O_NONBLOCK);
  pr_file_status_flag(STDIN_FILENO);
  printf("关闭`O_NONBLOCK'标志位后`STDIN_FILENO'的文件状态标志为:\n\t");
  clr_fl(STDIN_FILENO, O_NONBLOCK);
  pr_file_status_flag(STDIN_FILENO);
  printf("==============================\n");
  return 0;
}

