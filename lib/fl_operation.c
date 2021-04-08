/**
 * Filename: fl_operation.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/8/21
 * Description:
 *      文件描述符操作函数
 */
#include "apue.h"

int set_cloexec(int fd) {
  int cur_flag = 0;
  if((cur_flag = fcntl(fd, F_GETFD)) < 0) {
    return -1;
  }
  cur_flag |= FD_CLOEXEC;
  return fcntl(fd, F_SETFD, cur_flag);
}

void set_fl(int fd, int flags){
  int cur_flags = 0;
  if((cur_flags = fcntl(fd, F_GETFL))<0){
    err_sys("fcntl F_GETFL error");
  }
  cur_flags |= flags; // (turn on the specific flag bits)将新的标志为设置文件打开状态标志位
  if(fcntl(fd, F_SETFL, cur_flags) < 0){
    err_sys("fcntl F_SETFL error");
  }
}

void clr_fl(int fd, int flags){
  int cur_flags = 0;
  if((cur_flags = fcntl(fd, F_GETFL)) < 0){
    err_sys("fcntl F_GETFL error");
  }
  cur_flags &= ~flags; // (turn off the specific flag bits)
  if(fcntl(fd, F_SETFL, cur_flags) < 0){
    err_sys("fcntl F_SETFL error");
  }
}

void pr_file_status_flag(int fd) {
  int flags = 0;
  if ((flags = fcntl(fd, F_GETFL)) < 0) {
    err_sys("fcntl error for %d", fd);
  }
  switch (flags & O_ACCMODE) {
    case O_RDONLY:printf("read only");
      break;

    case O_WRONLY:printf("write only");
      break;

    case O_RDWR:printf("read write");
      break;

    default:err_dump("unknown access mode");
  }
  if (flags & O_APPEND) {
    printf(", append");
  }
  if (flags & O_NONBLOCK) {
    printf(", nonblocking");
  }
  if (flags & O_SYNC) {
    printf(", synchronous writes");
  }

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
  if(flags & O_FSYNC){
    printf(", synchronous writes");
  }
#endif
  putchar('\n');
}
