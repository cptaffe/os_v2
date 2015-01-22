
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <sys/io.h>

void outb(unsigned short port, unsigned char val) {
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

unsigned short inb(unsigned short port) {
	unsigned char ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}

// TODO: This is probably fragile.
void io_wait() {
	asm( "jmp 1f\n"
	"1:jmp 2f\n"
	"2:");
}
