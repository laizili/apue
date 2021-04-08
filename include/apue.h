//
// Created by laizili on 2020/12/11.
//

#ifndef UNIXPROG_INCLUDE_APUE_H_
#define UNIXPROG_INCLUDE_APUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _POSIX_C_SOURCE 200809L  // FEATURE TEST MACRO 功能測試宏

#include <stddef.h>  // for offsetof
// for convenience
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h> // for SIG_ERR
#include <fcntl.h>
#include <sys/stat.h>
#define MAXLINE 4096  /* max line length, 每行最大字符数量*/

/*
 * Default file access permission for new files.
 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)  /*新文件默认的文件访问权限,用户：读写，组用户读，其他用户读权限*/

/*
 * Default permissions for new directories
 */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH) /*新文件夹的默认访问权限*/

typedef void Sigfunc(int); /*for signal handler, 信号处理函数*/

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/*
 * prototypes for our own functions
 *
 */

// 第二章引入的库函数
char *path_alloc(size_t *sz);  /*Figure 2.16*/
long open_max(void);     /*Figure 2.17*/

// 第三章引入的库函数
int set_cloexec(int fd);   /* Figure 13.9 */
void clr_fl(int fd, int flags);   /* Figure 3.12 */
void set_fl(int fd, int flags);
// 打印文件状态标志
void pr_file_status_flag(int fd);
// TODO 每一节章节定义的函数

/*
 *
 *    函数名      从strerror添加字符串？     strerror的参数       终止？
 *    err_dump      是                     errno             abort()
 *    err_exit      是                     显示参数            exit(1)
 *    err_msg       否                       x               return
 *    err_quit      否                       x               exit(1)
 *    err_ret       是                     errno             return
 *    err_sys       是                     errno             exit(1)
 *    err_cont      是                     显示参数            return
 */
// 错误处理函数 Appendix B
void err_msg(const char *, ...);
void err_dump(const char *, ...) __attribute__((noreturn));
void err_quit(const char *, ...) __attribute__((noreturn));
void err_cont(int, const char *, ...);
void err_exit(int, const char *, ...) __attribute__((noreturn));
void err_ret(const char *, ...);
void err_sys(const char *, ...) __attribute__((noreturn));

//用于守护进程的出错处理函数

#ifdef __cplusplus
}
#endif //  END extern "C"
#endif //UNIXPROG_INCLUDE_APUE_H_
