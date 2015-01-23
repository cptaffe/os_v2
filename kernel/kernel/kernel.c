
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/kernel.h>
#include <kernel/file.h>
#include <kernel/tty.h>
#include <kernel/halt.h>
#include <kernel/int.h>
#include <sys/io.h>

static kernel main_kern = { .state = EXIT_SUCCESS };

kernel *kern0;

// kernel init run in _init
__attribute__((constructor))
void kernel_init() {
	kern0 = &main_kern;
}

// kernel messages are white w/ blue background.
static void kputs(char *msg) {
	// somewhat low level tty usage.
	tty *t = (tty *) stdout->out;
	uint8_t col = tty_getcolor(t);
	tty_setcolor(t, 15 | 1 << 4);
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

	kputs("testing interrupts...");

	asm("int $31");

	// handle late cleanup
	kernel_exit(kern);
}

void kernel_exit(kernel *kern) {

	// set tty color & print proper message.
	if (kern->state == EXIT_SUCCESS) {
		kputs("kernel has exited properly.");
	} else if (kern->state == EXIT_FAILURE) {
		kputs("kernel has panicked.");
	} else {
		kputs("kernel data corrupted.");
	}

	// hang execution of the kernel.
	hang();
}
