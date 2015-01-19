#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kerr(char *err) {
	uint8_t old_col = tty_getcolor(&tty_out);
	tty_setcolor(&tty_out, 4);
	printf(err);
	tty_setcolor(&tty_out, old_col);
}

void kernel_early() {
	// init the global out tty.
	tty_init(&tty_out);
	kerr("tty_out has been initialized.\n");
}

void kernel_main() {
	// use stdio's printf (uses tty).
	tty_setcolor(&tty_out, 15 | 1 << 4);
	printf("Hello from this OS's kernel!\n");

	// test vga memory usage
	uint8_t *vga_mem = (uint8_t *) 0xA0000000L;
	size_t offset = 50;
	vga_mem[offset] = 240;
}
