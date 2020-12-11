
#include "apue.h"
#include <errno.h> // for definition of errno , 错误代码
#include <stdarg.h> // ISO C variable arguments, C 变长参数
static void err_doit(int errorflag, int error, const char *fmt, va_list ap);

/**
 * Condition（使用条件）:
 *      Fatal error related to a system call.
 * Handle strategy（函数执行结果）:
 *      print a message and terminate.
 */
void err_sys(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}
/**
 * Fatal error related to a system call.
 * Print a message, dump core, and terminate.
 */
void err_dump(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort(); // dump core and terminate.
  exit(1); // shouldn't get here
}
/**
 * Non-fatal error related to a system call.
 * print a message and return.
 */
void err_ret(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}

/**
 * Non-fatal error unrelated to a system call.
 * Print a message and return.
 */
void err_msg(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}

/**
 * Non-fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * print a message and return.
 */
void err_cont(int error, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
}
/**
 * Fatal error unrelated to a system call.
 * Print a message ad terminate.
 */
void err_quit(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}
/**
 * Fatal error unrelated to a system call.
 * Error code passed as explicit parameter.
 * Print a message and terminate.
 */
void err_exit(int error, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
  exit(1);
}

/**
 *  Print a message and return to caller.
 *  Caller specifies "errorflag"
 */
static void err_doit(int errorflag, int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];
  // 打印用户消息
  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  if (errorflag) {
    unsigned long n = strlen(buf);
    snprintf(buf + n, MAXLINE - 1 - n, ": %s", strerror(error));
  }
  strcat(buf, "\n");
  fflush(stdout); /*in case stdout and stderr are the same*/ //TODO: 不懂为什么stdout stderr会相同（可能防止两者混合输出）*/
  fputs(buf, stderr);
  fflush(NULL);

}
