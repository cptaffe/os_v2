
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_VGA_H_
#define KERNEL_VGA_H_

#include <stdint.h>

// constants
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const uint16_t *VGA_MEMORY = (uint16_t *) 0xb8000;

enum vga_col {
	// colors (0 - 15)
	COLOR_BLACK,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROWN,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_LIGHT_BROWN,
	COLOR_WHITE,
};

static inline uint8_t make_color(enum vga_col fg, enum vga_col bg) {
	return fg | bg << 4;
}

static inline uint16_t make_vga_entry(char c, uint8_t color) {
	return ((uint16_t) c) | ((uint16_t) color) << 8;
}

#endif // KERNEL_VGA_H_
