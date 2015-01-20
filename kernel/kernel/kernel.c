
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/file.h>
#include <kernel/tty.h>

// TODO: fprintf

typedef struct {
	int test;
} kernel;

static kernel main_kern;
kernel *kern0;

void kernel_early() {
	// early kernel stuffs, runs before global constructors
	kern0->test = 50;
}

void kernel_main(kernel *kern) {

	if (kern->test == 50) {
		printf("It worked.\n");
	} else {
		printf("Fail.\n");
	}

	// use stdio's printf (uses tty).
	printf("Hello from this OS's kernel!\n");
	printf("LOLOLOLOLOLOLOLOLOLOLOLOLOL\n");

	// switch ttys
	// old tty is set as inactive
	tty *old_tty = (tty *) stdout->out;
	tty_detach(old_tty);

	printf("This tty is now inactive!\n");


	file *old_stdout = stdout;
	tty new_tty;
	file new_file;
	stdout = file_open(&new_file, FILE_TTY, &new_tty);

	printf("THIS IS A NEW TTY, BITCHES!\n");

	tty_detach(&new_tty);
	tty_attach(old_tty, 0xb8000, 80, 25);
	stdout = old_stdout;

	printf("just testing....\n");
}
