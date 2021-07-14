#ifndef LS_H
#define LS_H

#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>

int strcmp(const char *x, const char *y);
int display_error(char *name, char *dir_name);

#endif /* LS_H */
