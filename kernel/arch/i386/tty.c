#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/io.h>

#include <kernel/vga.h>
#include <kernel/tty.h>

// utility functions

// cursor location
static void tty_cursor_pos(int row, int col) {
	unsigned short position=(row*80) + col;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void tty_init(tty *t) {
	t->col = 0;
	t->row = 0;
	t->color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);

	t->vga_buf = (uint16_t *) VGA_MEMORY;

	t->height = VGA_HEIGHT;
	t->width = VGA_WIDTH;

	// set inactive by default
	t->opts = TTY_INACTIVE;
	t->buf = (uint16_t *) t->bufmem;

	int16_t fill = make_vga_entry(' ', t->color);
	for (size_t i = 0; i < (t->height * t->width); i++ ) {
		t->buf[i] = fill;
	}
}

void tty_setcolor(tty *t, uint8_t color) {
	t->color = color;
}

uint8_t tty_getcolor(tty *t) {
	return t->color;
}

void tty_putentryat(tty *t, char c, uint8_t color, size_t x, size_t y) {
	t->buf[(y * t->width) + x] = make_vga_entry(c, color);
}

void tty_putchar(tty *t, char c) {

	// special characters
	if (c == '\r') {
		t->col = 0; // return
	} else if (c == '\a') {
		// bell
	} else if (c == '\b') {
		if (t->col > 0) {
			t->col--;
		} else {
			// not enough info
		}
		tty_putentryat(t, ' ', t->color, t->col, t->row);
	} else if (c == '\t') {
		// tabular (8 characters)
		int ntab = (8 - (t->col % 8));
		for (int i = 0; i < ntab; i++) {
			tty_putchar(t, ' '); // proper space handling
		}
	} else {
		if (c != '\n') {
			tty_putentryat(t, c, t->color, t->col, t->row);
		}

		// looping check
		if (++t->col == t->width || c == '\n') {
			t->col = 0;
			if (++t->row == t->height) {
				// shift all rows up one
				memcpy(t->buf, &t->buf[VGA_WIDTH], (((t->height - 1) * 2) * (t->width * 2)));
				t->row = t->height - 1; // stick at bottom row
			}
		}

		// position cursor at current col & row
		tty_cursor_pos(t->row, t->col);
	}
}

void tty_putstr(tty *t, const char *data) {
	tty_write(t, data, strlen(data));
}

size_t tty_write(tty *t, const char *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		tty_putchar(t, data[i]);
	}
	return size; // all was written
}

void tty_attach(tty *t, int16_t *mem, size_t width, size_t height) {
	t->opts |= TTY_ACTIVE;

	t->width = width;
	t->height = height;
	t->vga_buf = (int16_t *) mem;

	// buffer current buffer to vga buffer
	for (size_t i = 0; i < (t->height * t->width); i++ ) {
		t->vga_buf[i] = t->buf[i];
	}

	// switch buf ptr
	t->buf = t->vga_buf;
}

void tty_detach(tty *t) {
	t->opts |= TTY_INACTIVE;

	// switch buf ptr
	t->buf = (uint16_t *) t->bufmem;

	// buffer current buffer to vga buffer
	for (size_t i = 0; i < (t->height * t->width); i++ ) {
		t->buf[i] = t->vga_buf[i];
	}
}
