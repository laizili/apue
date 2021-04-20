/**
 * Filename: fig6-2_getpwnam.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/20/21
 * Description:
 * 
 */
#include <string.h>
#include <stdio.h>
#include <pwd.h>

struct passwd *c_getpwnam(const char *username) {
  struct passwd *pw = NULL;
  setpwent();
  while ((pw = getpwent()) != NULL) {
    if (strcmp(username, pw->pw_name) == 0) {
      break;
    }
  }
  endpwent();
  return pw;
}

// c_getpwnam测试程序，输入用户名，输出相应的数值ID号
int main(int argc, char *argv[]) {
  struct passwd *pw;
  if (argc != 2) {
    fprintf(stderr, "usage: %s username\n", argv[0]);
  }
  if ((pw = c_getpwnam(argv[1])) != NULL) {
    printf("username: %s, uid: %u\n", argv[1], pw->pw_uid);
  } else {
    printf("not found this user: %s\n", argv[1]);
  }

  return 0;
}

