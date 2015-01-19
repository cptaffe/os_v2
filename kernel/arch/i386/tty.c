#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>
#include <kernel/tty.h>

tty tty_out; // implement extern

void tty_init(tty *t) {
	t->row = 0;
	t->col = 0;
	t->color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	t->buf = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t i = y * VGA_WIDTH + x;
			t->buf[i] = make_vga_entry(' ', t->color);
		}
	}
}

void tty_setcolor(tty *t, uint8_t color) {
	t->color = color;
}

void tty_putentryat(tty *t, char c, uint8_t color, size_t x, size_t y) {
	const size_t i = y * VGA_WIDTH + x;
	t->buf[i] = make_vga_entry(c, color);
}

void tty_putchar(tty *t, char c) {

	if (c != '\n') {
		tty_putentryat(t, c, t->color, t->col, t->row);
	}

	if (++t->col == VGA_WIDTH || c == '\n') {
		t->col = 0;
		if (++t->row == VGA_HEIGHT) {
			// shift all rows up one
			memcpy(t->buf, &t->buf[VGA_WIDTH], (VGA_HEIGHT - 1) * VGA_WIDTH);
			t->row = VGA_HEIGHT - 1; // stick at bottom row
		}
	}
}

void tty_putstr(tty *t, const char *data) {
	tty_write(t, data, strlen(data));
}

void tty_write(tty *t, const char *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		tty_putchar(t, data[i]);
	}
}
