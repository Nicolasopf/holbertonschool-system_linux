#ifndef LS_H
#define LS_H

#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>

int strcmp(const char *x, const char *y);
int display_error(char *name, char *dir_name);
int ls_a(int argc, char *argv[]);
int strchar(char *str, char a);
int check_arguments(int argc, char *argv[], char *options);



#endif /* LS_H */
