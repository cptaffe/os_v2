#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/file.h>

// TODO: fprintf

typedef struct {
	file *out;
} kernel;

void kernel_early() {
	// early kernel stuffs, runs before global constructors
}

void kernel_main() {
	// use stdio's printf (uses tty).
	printf("Hello from this OS's kernel!\n");
}
