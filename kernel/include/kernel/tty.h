
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_TTY_H_
#define KERNEL_TTY_H_

#include <stddef.h>
#include <stdint.h>

// stucture of a tty
typedef struct {
	size_t row;
	size_t col;
	uint8_t color;
	uint16_t *buf;
} tty;

extern tty tty_out;

void tty_init(tty *t);
void tty_putchar(tty *t, char c);
void tty_putstr(tty *t, const char *data);
void tty_write(tty *t, const char *data, size_t size);

// character putting without affecting tty values.
void tty_col_put(tty *t, uint8_t col, char c);
void tty_colpos_put(tty *t, size_t x, size_t y, uint8_t col, char c);

// color setting
void tty_setcolor(tty *t, uint8_t color);
uint8_t tty_getcolor(tty *t);

// terminal dimensions
size_t tty_getmaxx(tty *t);
size_t tty_getmaxy(tty *t);

void tty_cursor_pos(int row, int col);

#endif // KERNEL_TTY_H_
