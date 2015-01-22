
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/int.h>
#include <sys/io.h>

static idt_state idt_local = {
	.entry = {{0}},
	.ptr = {0},
	.pic_base = 32,
	.pic_masks = {0x0, 0x0}
};

static void *int_handlers[] = {
	(void *) &int_handler_0,
	(void *) &int_handler_1,
	(void *) &int_handler_2,
	(void *) &int_handler_3,
	(void *) &int_handler_4,
	(void *) &int_handler_5,
	(void *) &int_handler_6,
	(void *) &int_handler_7,
	(void *) &int_handler_8,
	(void *) &int_handler_9,
	(void *) &int_handler_10,
	(void *) &int_handler_11,
	(void *) &int_handler_12,
	(void *) &int_handler_13,
	(void *) &int_handler_14,
	(void *) &int_handler_15,
	(void *) &int_handler_16,
	(void *) &int_handler_17,
	(void *) &int_handler_18,
	(void *) &int_handler_19,
	(void *) &int_handler_20,
	(void *) &int_handler_21,
	(void *) &int_handler_22,
	(void *) &int_handler_23,
	(void *) &int_handler_24,
	(void *) &int_handler_25,
	(void *) &int_handler_26,
	(void *) &int_handler_27,
	(void *) &int_handler_28,
	(void *) &int_handler_29,
	(void *) &int_handler_30,
	(void *) &int_handler_31,
	(void *) &int_handler_32,
	(void *) &int_handler_33,
	(void *) &int_handler_34,
	(void *) &int_handler_35,
	(void *) &int_handler_36,
	(void *) &int_handler_37,
	(void *) &int_handler_38,
	(void *) &int_handler_39,
	(void *) &int_handler_40
};

// set up handler
void idt_set(idt_state *idts, uint8_t num, void *handle, uint16_t sel, uint8_t flags) {
	uint32_t base = (uint32_t) handle;
	idts->entry[num].sel = sel;
	idts->entry[num].flags = flags;
	idts->entry[num].base_hi = (base >> 16) & 0xffff;
	idts->entry[num].base_lo = (base & 0xffff);
}

idt_state *idt_init() {
	idt_state *idt = &idt_local;
	idt->ptr.limit = (uint16_t) sizeof(idt->entry) - 1;
	idt->ptr.base = (uint32_t) &(idt->entry);

	// set up kbrd interrupt at irq 1
	for (uint32_t i = 0; i < 40; i++) {
		idt_set(idt, i, int_handlers[i], 0x08, 0x8E);
	}
	// set up pic after 0-31 (reserved)
	pic_init(idt->pic_base, idt->pic_base + 8);

	// apply masks
	outb(0x21, idt->pic_masks[0]);
	outb(0xa1, idt->pic_masks[1]);

	idt_ptr *ptr = &(idt->ptr);
	asm("lidt (%0)"::"r"(ptr));
	asm("sti");

	return idt;
}
