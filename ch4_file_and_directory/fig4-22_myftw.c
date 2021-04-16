/**
 * Filename: fig4-22_myftw.c
 * Author:   csbonkers
 * Contact:  csbonkers@mail.ynu.edu.cn
 * Date:     4/12/21
 * Description:
 *    遍历文件系统层次结构，统计各类文件的分布
 */
#include <limits.h>
#include <dirent.h>
#include "apue.h"

//  文件类型枚举：除目录外的其他文件、目录文件、不能读取目录项的目录文件、不能获取`struct stat'文件信息的任意文件
enum filetype { FTW_F, FTW_D, FTW_DNR, FTW_NS };

// 定义了一个函数类型
typedef int Myfunc(const char *path, const struct stat *sb, enum filetype ft);
static Myfunc myfunc;

// file tree walk function
static int myftw(const char *sdir, Myfunc *fn);
static int dopath(Myfunc *fn);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    err_quit("usage: %s <staring_pathname>", argv[0]);
  }
  int ret = myftw(argv[1], myfunc);
  ntot = nsock + nslink + nfifo + nchr + nblk + nreg + ndir;
  ntot = ntot > 0 ? ntot : 1;
  printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories    = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block special  = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("char special   = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("FIFOS          = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);
  return ret;
}
// contains the full pathname for every file(遍历目录树过程中：相对于遍历起点目录的文件路径)
static char *fullpath;
static size_t pathlen;

static int myftw(const char *sdir, Myfunc *fn) {
  fullpath = path_alloc(&pathlen);
  if (pathlen <= strlen(sdir)) {
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
      err_sys("realloc failed");
    }
  }
  strcpy(fullpath, sdir);
  int ret = dopath(fn);
  free(fullpath);
  return ret;
}

static int dopath(Myfunc *fn) { // 四个递归出口
  struct stat sb;
  if (lstat(fullpath, &sb) < 0) { // can't stat
    return fn(fullpath, NULL, FTW_NS);
  }
  if (!S_ISDIR(sb.st_mode)) { // files other than directory
    return fn(fullpath, &sb, FTW_F);
  }
  int ret;
  if ((ret = fn(fullpath, &sb, FTW_D)) != 0) { // directory
    return ret;
  }
  size_t sn = strlen(fullpath); // 当前文件路径的长度
  if (sn + NAME_MAX + 2 > pathlen) { // expand path buffer
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
      err_sys("realloc failed"); // 结束进程
    }
  }
  fullpath[sn++] = '/';
  fullpath[sn] = '\0';
  DIR *dp; // directory stream object
  if ((dp = opendir(fullpath)) == NULL) {
    return fn(fullpath, NULL, FTW_DNR);
  }
  struct dirent *pentry; // 目录项结构指针
  while ((pentry = readdir(dp)) != NULL) {
    if (strcmp(".", pentry->d_name) == 0 || strcmp("..", pentry->d_name) == 0) {
      continue;
    }
    strcpy(fullpath + sn, pentry->d_name);
    if ((ret = dopath(fn)) != 0) { // 递归遍历
      break;
    }
  }
  fullpath[sn - 1] = '\0';
  if (closedir(dp) < 0) {
    err_ret("can't close directory %s", fullpath);
  }
  return ret;
}

int myfunc(const char *pathname, const struct stat *psb, enum filetype ft) {
  switch (ft) {
    case FTW_F:
      switch (psb->st_mode & S_IFMT) {
        case S_IFREG:nreg++;
          break;
        case S_IFBLK:nblk++;
          break;
        case S_IFCHR:nchr++;
          break;
        case S_IFIFO:nfifo++;
          break;
        case S_IFLNK:nslink++;
          break;
        case S_IFSOCK:nsock++;
          break;
        case S_IFDIR:err_dump("for S_IFDIR for %s", pathname);
      }
      break;
    case FTW_D:ndir++;
      break;
    case FTW_DNR:err_ret("can't read directory %s", fullpath);
      break;
    case FTW_NS:err_ret("stat error for %s", fullpath);
      break;
    default:err_dump("unknow type %d for pathname %s", ft, pathname);
  }
  return 0; // 文件类型统计函数总是返回 0
}