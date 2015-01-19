#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kprint(char *str) {
	uint8_t old_col = tty_getcolor(&tty_out);
	tty_setcolor(&tty_out, 15 | 1 << 4);
	printf(str);
	tty_setcolor(&tty_out, old_col);
}

void kernel_early() {
	// init the global out tty.
	tty_init(&tty_out);
}

void kernel_main() {
	// use stdio's printf (uses tty).
	kprint("Hello from this OS's kernel!\n");
}
