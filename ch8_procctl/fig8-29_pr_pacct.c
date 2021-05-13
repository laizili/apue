/**
 * Filename: fig8-29_pr_pacct.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     5/12/21
 * Description:
 *     打印从系统会计文件中选出字段
 *
 *     注意：
 *          - ac_io 在linux中未使用，所以总是为 0
 *          - 使用进程会计功能可能需要安装 accton 程序(ubuntu: sudo apt install accton)
 */
#include "apue.h"
#include <sys/acct.h>
#define FMT "%-*.*s e = %6ld, chars = %7ld, %c %c %c %c\n"

#ifdef Linux
#define acct acct_v3
#else
#error only woring in linux platform
#endif
#if !defined(HAS_ACORE)
#define ACORE 0
#endif
#if !defined(HAS_AXSIG)
#define AXSIG 0
#endif

#if !defined(BSD)
// convert comp_t to unsigned long
// comp_t
// 3bit 8 base exponent; 13 bit fraction
static inline unsigned long compt2ulong(comp_t comptime) {
  unsigned long res = (comptime & 0x1fff) << ((comptime >> 13 & 7) * 3);
  return res;
}

#endif

int main(int argc, char *argv[]) {
  if (argc != 2) {
    err_quit("usage: %s acct_filename", argv[0]);
  }
  struct acct acdata;
  FILE *fp;
  if ((fp = fopen(argv[1], "r")) == NULL) {
    err_sys("can't open %s", argv[1]);
  }
  while (fread(&acdata, sizeof(struct acct), 1, fp) == 1) {
    printf(FMT,
           (int) sizeof(acdata.ac_comm),
           (int) sizeof(acdata.ac_comm),
           acdata.ac_comm,
           compt2ulong(acdata.ac_etime),
           compt2ulong(acdata.ac_io),
           acdata.ac_flag & ACORE ? 'D' : ' ',
           acdata.ac_flag & AXSIG ? 'X' : ' ',
           acdata.ac_flag & AFORK ? 'F' : ' ',
           acdata.ac_flag & ASU ? 'S' : ' '
    );
  }
  if (ferror(fp)) {
    err_sys("read error");
  }
  return 0;
}