//
// Created by laizili on 1/20/21.
//

#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int main(int argc, char *argv[]) {
    pr_sysconf("POSIXVERSION", _SC_VERSION);
    pr_pathconf("FILE_SIZE", "/home/laizili/", _PC_FILESIZEBITS);

    return 0;
}

static void pr_sysconf(char *mesg, int name) {
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL) {
                fputs(" (not supported)\n", stderr);
            } else {
                err_sys("sysconf error");
            }
        } else {
            fputs(" (no limit)\n", stdout);
        }
    } else {
        printf(" %ld\n", val);
    }
}

static void pr_pathconf(char *mesg, char *path, int name) {
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL) {
                fputs(" (not supported)\n", stdout);
            } else {
                err_sys("pathconf error, path = %s", path);
            }
        } else {
            fputs(" (no limit)\n", stdout);
        }
    } else {
        printf(" %ld\n", val);
    }
}
