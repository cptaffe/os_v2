
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_FILE_H_
#define KERNEL_FILE_H_

#include <stddef.h>
#include <stdint.h>

enum file_type {
	FILE_TTY
};

typedef struct {
	enum file_type type;
	void *out;
} file;

// generic output file
extern file *stdout;

// file i/o
file *file_open(file *file, enum file_type type, void *out);
size_t file_write(file *f, void *mem, size_t size);
size_t file_read(file *f, void *mem, size_t size);

#endif // KERNEL_FILE_H_
