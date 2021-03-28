#!/usr/bin/env python3
# -*- coding: utf8 -*-
from utils import csv_reader
from io import FileIO
import sys

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("usage: make_detector.py <path/to/sysconf_symfile> <path/to/pathconf_symfile> <output_filename>")
        exit(1)
    with FileIO(sys.argv[3], "wb") as out:
        header = \
            r"""/*
 *This file was created by python script, don't modify this file directly.
 */
#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);
int main(int argc, char **argv){
    if(argc != 2){
        err_quit("usage: a.out <dirname>");
    }
"""
        template_sysconf_defector = \
            r"""
#ifdef {0}
    printf("{0} defined to be %ld\n", (long){0} + 0);
#else
    printf("no symbol for {0}\n");
#endif

#ifdef {1}
    pr_sysconf("{0} =", {1});
#else
    printf("no symbol for {1}\n");
#endif
"""
        fragment = []
        rows = csv_reader(sys.argv[1])
        for row in rows:
            fragment.append(template_sysconf_defector.format(row[0], row[1]))

        template_pathconf_defector = \
            r"""
#ifdef {0}
    printf("{0} defined to be %ld\n", (long){0} + 0);
#else
    printf("no symbol for {0}\n");
#endif
#ifdef {1}
    pr_pathconf("{0} =", argv[1], {1});
#else
    printf("no symbol for {1}\n");
#endif
"""
        rows = csv_reader(sys.argv[2])
        for row in rows:
            fragment.append(template_pathconf_defector.format(row[0], row[1]))
        body = "".join(fragment)
        footer = \
            r"""}

static void pr_sysconf(char *mesg, int name)
{
    long ret;
    fputs(mesg,stdout);
    errno = 0;
    if((ret = sysconf(name)) < 0){
        if(errno != 0){
            if(errno == EINVAL){
                fputs(" (not supported)\n", stdout);
            }else{
                err_sys("sysconf error");
            }
        }else{
            fputs(" (no limit)\n", stdout);
        }
    }else{
        printf(" %ld\n", ret);
    }
}
    
static void pr_pathconf(char *mesg, char *path, int name)
{
    long ret;
    fputs(mesg, stdout);
    if((ret = pathconf(path, name)) < 0){
        if(errno != 0){
            if(errno == EINVAL){
                fputs("(not supported)\n", stdout);
            }else{
                printf("pathconf error, path = %s\n", path);
            }
        }else{
            fputs(" (no limits)\n", stdout);
        }
    }else{
        printf(" %ld\n", ret);
    }  
}
"""
        out.write((header + body + footer).encode("utf8"))
        print(sys.argv[3] + "源文件构建完成")
