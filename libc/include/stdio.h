
#ifndef STDIO_H_
#define STDIO_H_

#include <sys/cdefs.h>

int fprintf(const char* __restrict, ...);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#endif // STDIO_H_
