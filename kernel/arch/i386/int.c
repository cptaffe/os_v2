
#include <kernel/kernel.h>
#include <kernel/int.h>
#include <sys/io.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <stdio.h>

void int_handler(kernel *kern, int_info *intr) {

	printf("interrupt heard.\n");

	if (intr->num > 31) {
		int irq = intr->num - 31;
		printf("got irq #%d!\n", irq);
		if (irq == 7) {
			outb(0x20, 0x0B);
		 	uint8_t irr = inb(0x20);
			if (!(irr & 0x80)) {
				return;
			}
		}
		if (irq == 1) {
			uint16_t scancode = inb(0x60);
			printf("got keycode %d\n", scancode);
		}
		pic_eoi(irq);
	}
}
