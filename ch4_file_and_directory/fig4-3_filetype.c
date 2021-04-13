/**
 * Filename: fig4-3_filetype.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/9/21
 * Description:
 *     对每个命令行参数打印其文件类型
 */

#include "apue.h"

int main(int argc, char *argv[]) {
  struct stat sb;
  for (int i = 1; i < argc; ++i) {
    if (lstat(argv[i], &sb) == -1) {
      err_ret("lstat file `%s' error", argv[i]);
      continue;
    }
    const char *pstr = NULL;
    if (S_ISREG(sb.st_mode)) {
      pstr = "regular";
    } else if (S_ISDIR(sb.st_mode)) {
      pstr = "directory";
    } else if (S_ISCHR(sb.st_mode)) {
      pstr = "character special";
    } else if (S_ISLNK(sb.st_mode)) {
      pstr = "symbolic link";
    } else if (S_ISBLK(sb.st_mode)) {
      pstr = "block special";
    } else if (S_ISFIFO(sb.st_mode)) {
      pstr = "fifo";
    } else if (S_ISSOCK(sb.st_mode)) {
      pstr = "socket";
    } else {
      pstr = "** unknown mode **";
    }
    printf("%s: %s\n", argv[i], pstr);
  }
  return 0;
}