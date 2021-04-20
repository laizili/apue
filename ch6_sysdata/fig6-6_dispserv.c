/**
 * Filename: fig6-6_dispserv.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/20/21
 * Description:
 * 
 */

#include "apue.h"
#include <netdb.h>
#include <netinet/in.h> // 获取字节序转换函数

int main(int argc, char *argv[]) {
  struct servent *pserv;
  for (int i = 1; i < argc; ++i) {
    if ((pserv = getservbyname(argv[i], NULL)) == NULL) {
      printf("error: not found \"%s\" service entry\n", argv[i]);
      printf("=================================================\n");

      continue;
    }
    printf("service name: %s\n", pserv->s_name);
    printf("\tport: %hd\n", htons(pserv->s_port)); /* pserv指向的结构体对象中，端口号（s_port）以网络字节序（big-endian）存储,
  转换为主机序（little-endian）,以正确显示 */
    printf("service aliases: ");
    for (const char *aname = (*pserv->s_aliases); aname != NULL; ++aname) {
      printf("%s ", aname);
    }
    printf("\n");
    printf("protocol: %s\n", pserv->s_proto);
    printf("=================================================\n");
  }
  return 0;
}
