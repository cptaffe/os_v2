
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/file.h>
#include <kernel/tty.h>

// TODO: fprintf

enum kernel_state {
	EXIT_SUCCESS,
	EXIT_FAILURE
};

typedef struct {
	enum kernel_state state;
} kernel;

static kernel main_kern = {
	.state = EXIT_SUCCESS
};

kernel *kern0;

// early setup befor _init
void kernel_early(kernel *kern) {
	// cannot print yet, setup has not occured.
	kern0 = &main_kern;
}

// called after kernel_early & _init
void kernel_main(kernel *kern) {

	// use stdio's printf (uses tty).
	printf("Hello from this OS's kernel!\n");

	// switch ttys
	// old tty is set as inactive
	tty *old_tty = (tty *) stdout->out;
	tty_detach(old_tty);

	printf("This tty is now inactive.\n");


	file *old_stdout = stdout;
	tty new_tty;
	file new_file;
	stdout = file_open(&new_file, FILE_TTY, &new_tty);

	printf("This is printed on a new tty.\n");

	tty_detach(&new_tty);
	tty_attach(old_tty, 0xb8000, 80, 25);
	stdout = old_stdout;

	printf("This tty is now again active.\n");
}

// late cleanup after _fini
void kernel_late(kernel *kern) {

	if (kern->state == EXIT_SUCCESS) {
		printf("kernel has exited properly.\n");
	} else if (kern->state == EXIT_FAILURE) {
		printf("kernel has panicked.\n");
	}
}
