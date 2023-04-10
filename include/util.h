#ifndef __UTIL_H
#define __UTIL_H

#define STR(X) XSTR(X)
#define XSTR(X) #X

#define MAX_SIZE 1024

void
str_rst(char* str);

char*
str_n_dup(const char* s, size_t max);

#endif