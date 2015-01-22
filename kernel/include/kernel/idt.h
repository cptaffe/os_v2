
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_IDT_H_
#define KERNEL_IDT_H_

#include <stddef.h>
#include <stdint.h>

// idt entry
typedef struct {
	uint16_t base_lo;
	uint16_t sel; // kernel segment
	uint8_t zero; // always 0
	uint8_t flags; // Set using the above table
	uint16_t base_hi;
} __attribute__ ((__packed__)) idt_entry;

// idt pointer
typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((__packed__)) idt_ptr;

typedef struct {
	idt_entry entry[256];
	idt_ptr ptr;
	uint8_t pic_base;
	uint16_t pic_masks[2];
} idt_state;

// sets an interrupt with a handler
void idt_set(idt_state *idt, uint8_t num, void *handle, uint16_t sel, uint8_t flags);

idt_state *idt_init();

#endif // KERNEL_IDT_H_
