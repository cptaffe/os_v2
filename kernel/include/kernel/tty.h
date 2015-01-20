
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_TTY_H_
#define KERNEL_TTY_H_

#include <stddef.h>
#include <stdint.h>

enum tty_options {
	// cannot be active & inactive
	TTY_INACTIVE = 0 << 0,
	TTY_ACTIVE = 1 << 0,
};

// stucture of a tty
typedef struct {
	size_t width;
	size_t height;
	size_t row;
	size_t col;
	uint8_t color;

	// vga buffer location
	uint16_t *vga_buf;

	// double buffering
	uint16_t *buf;
	uint16_t bufmem[25][80];

	// options
	enum tty_options opts;
} tty;

void tty_init(tty *t);
void tty_putchar(tty *t, char c);
void tty_putstr(tty *t, const char *data);
size_t tty_write(tty *t, const char *data, size_t size);

// color setting
void tty_setcolor(tty *t, uint8_t color);
uint8_t tty_getcolor(tty *t);

// activate & deactivate
void tty_attach(tty *t, int16_t *mem, size_t width, size_t height);
void tty_detach(tty *t);

#endif // KERNEL_TTY_H_
