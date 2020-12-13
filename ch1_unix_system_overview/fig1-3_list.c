/*
 * File: fig1-3_list.c (Page 4)
 *    列出一个目录中所有文件(名)
 */
#include "apue.h"
#include <dirent.h>

int main(int argc, char **argv) {
  if(argc != 2){
    err_quit("Usage: %s <dirname>", argv[0]);
  }
  DIR *dirp = NULL;
  struct dirent *direntp = NULL;
  if ( (dirp = opendir(argv[1])) == NULL){
    err_sys("can't open %s", argv[1]);
  }
  while ((direntp = readdir(dirp)) != NULL){
    printf("%s\n", direntp->d_name);
  }
  return 0;
}