/**
 * Filename: fig3-2_file_with_hole.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/5/21
 * Description:
 *      创建一个具有空洞的文件
 */

#include "apue.h"

char buf1[] = "abcdefghij";  // strlen(buf1) -> 10
char buf2[] = "ABCDEFGHIJ"; // strlen(buf2) -> 10

int main(int argc, char *argv[]) {
  int fd;
  if ((fd = creat("file.hole", FILE_MODE)) < 0) {
    err_sys("create error");
  }

  const int wn_buf1 = sizeof(buf1) - 1;
  if (write(fd, buf1, wn_buf1) != wn_buf1) {
    err_sys("buf1 write error");
  }

  /* file offset now at 10 */
  if (lseek(fd, 16384, SEEK_SET) == -1) {
    err_sys("lseek error");
  }
  /* file offset now at 16384 */
  const int wn_buf2 = sizeof(buf2) - 1;
  if (write(fd, buf2, wn_buf2) != wn_buf2) {
    err_sys("buf2 write error");
  }
  /* file offset now at 16394 */

  // 最终文件大小为： 30 bytes
  return 0;
}