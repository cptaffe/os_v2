
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/kernel.h>
#include <kernel/file.h>
#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/halt.h>
#include <kernel/int.h>
#include <kernel/syscall.h>
#include <sys/io.h>

static kernel main_kern = { .state = EXIT_SUCCESS };

kernel *kern0;

// kernel init run in _init
__attribute__((constructor))
void kernel_init() {
	kern0 = &main_kern;
}

enum kputs_priority {
	KPUTS_WARN,
	KPUTS_ERR,
	KPUTS_MSG,
};

// kernel messages are white w/ blue background.
static void kputs(char *msg, enum kputs_priority priority) {
	// somewhat low level tty usage.
	tty *t = (tty *) stdout->out;
	uint8_t col = tty_getcolor(t);
	tty_puts(t, "k: ");
	uint8_t ncol;
	if (priority == KPUTS_WARN) {
		ncol = COLOR_WHITE | (COLOR_BROWN << 4);
	} else if (priority == KPUTS_ERR) {
		ncol = COLOR_WHITE | (COLOR_RED << 4);
	} else {
		ncol = COLOR_WHITE | (COLOR_BLUE << 4);
	}
	tty_setcolor(t, ncol);
	tty_puts(t, msg); tty_putc(t, '\n');
	tty_setcolor(t, col);
}

// early setup befor _init
void kernel_early() { }

// called after kernel_early & _init
void kernel_main(kernel *kern) {

	// set up interrupt descriptor table
	kern0->idt = idt_init();

	// use stdio's printf (uses tty).
	printf("Hello from this OS's kernel!\n");

	kputs("testing interrupts...", KPUTS_MSG);

	uint32_t i = check_syscall();
	printf("got %d\n", (int) i);

	// handle late cleanup
	kernel_exit(kern);
}

void kernel_exit(kernel *kern) {

	// set tty color & print proper message.
	if (kern->state == EXIT_SUCCESS) {
		kputs("kernel has exited properly.", KPUTS_MSG);
	} else if (kern->state == EXIT_FAILURE) {
		kputs("kernel has panicked.", KPUTS_ERR);
	} else {
		kputs("kernel data corrupted.", KPUTS_ERR);
	}

	// hang execution of the kernel.
	hang();
}
