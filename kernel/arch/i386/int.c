
#include <kernel/kernel.h>
#include <kernel/int.h>
#include <sys/io.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/syscall.h>
#include <kernel/kbd.h>
#include <stdio.h>


void int_handler(kernel *kern, int_info *intr) {

	// deal with irq codes
	if (intr->num > 31 && intr->num <= 40) {
		int irq = intr->num - 31;
		// printf("got irq #%d!\n", irq);
		if (irq == 1 || irq == 2) {
			int keycode = inb(0x60);
			kbd_int(keycode);
		} else if (irq == 7) {
			outb(0x20, 0x0B);
		 	uint8_t irr = inb(0x20);
			if (!(irr & 0x80)) {
				return;
			}
		}
		pic_eoi(irq);
	}
}
