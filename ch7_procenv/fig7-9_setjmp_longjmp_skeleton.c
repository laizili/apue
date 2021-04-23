/**
 * Filename: fig7-9_setjmp_longjmp_skeleton.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/23/21
 * Description:
 *     命令处理程序的典型骨架部分
 */

#include "apue.h"
#include <setjmp.h>
#define TOK_ADD 5

void do_line(char *);
void cmd_add();
int get_token();

jmp_buf jmpbuffer;

int main(int argc, char *argv[]) {
  char line[MAXLINE];
  if (setjmp(jmpbuffer) != 0) {
    printf("error");
  }
  while (fgets(line, MAXLINE, stdin) != NULL) {
    do_line(line);
  }
  return 0;
}

char *tok_ptr; /* global pointer for get_token() */
void do_line(char *ptr) { /* process one line of input */
  int cmd;
  tok_ptr = ptr;
  while ((cmd = get_token()) > 0) {
    switch (cmd) { /* one case for each command */
      case TOK_ADD:cmd_add();
        break;
    }
  }
}

void cmd_add() {
  int token = get_token();
  if (token < 0) { /* an error has occurred */
    longjmp(jmpbuffer, 1);
  }
  /* rest of processing for this command */
}
int get_token() {
  /* fetch next token from line pointed to by tok_ptr */
  return 0;
}