
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_H_
#define KERNEL_H_

#include <kernel/idt.h>

enum kernel_state {
	EXIT_FAILURE,
	EXIT_SUCCESS
};

typedef struct {
	enum kernel_state state;
	idt_state *idt;
} kernel;

// global kernel function
extern kernel *kern0;

// functions
void kernel_early();
void kernel_exit(kernel *kern);
void kernel_main(kernel *kern);

#endif // KERNEL_H_
