#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early() {
	// init the global out tty.
	tty_init(&tty_out);
}

void kernel_main() {
	// use stdio's printf (uses tty).
	char str[] = "Hello, kernel World! x\n";
	for (int i = 0; i < 26; i++) {
		str[sizeof(str) - 3] = 'A' + i;
		printf(str);
	}
}
