#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/file.h>
#include <kernel/tty.h>

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
	printf("LOLOLOLOLOLOLOLOLOLOLOLOLOL\n");

	// switch ttys
	// old tty is set as inactive
	tty *old_tty = (tty *) stdout->out;
	tty_deactivate(old_tty);

	printf("This tty is now inactive!\n");


	file *old_stdout = stdout;
	tty new_tty;
	file new_file;
	stdout = file_open(&new_file, FILE_TTY, &new_tty);

	printf("THIS IS A NEW TTY, BITCHES!\n");

	tty_deactivate(&new_tty);
	tty_activate(old_tty);
	stdout = old_stdout;

	printf("just testing....\n");
}
