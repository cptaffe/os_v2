
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#include <stdint.h>

#include <kernel/pic.h>
#include <sys/io.h>

// slave pic main and data ports
static const uint8_t mp = 0x20;
static const uint8_t mpd = 0x21;

// slave pic main and data ports
static const uint8_t sp = 0xa0;
static const uint8_t spd = 0xa1;

static const uint8_t eoi = 0x20;

static inline void outb_wait(uint16_t port, uint8_t msg) {
	outb(port, msg);
	io_wait();
}

// send end of interrupt signal
void pic_eoi(uint8_t irq) {
	if (irq >= 8) {
		outb(sp, eoi); // send eoi to slave
	}
	outb(mp, eoi);
}

// pic remapping
void pic_init(uint8_t off1, uint8_t off2) {
	// save masks
	uint8_t mmsk = inb(mpd), smsk = inb(spd);

	// start init
	outb_wait(mp, 0x11);
	outb_wait(sp, 0x11);

	// vector offset
	outb_wait(mpd, off1);
	outb_wait(spd, off2);

	// inform pics of master/slave relationship
	outb_wait(mpd, 0x04);
	outb_wait(spd, 0x02);

	outb_wait(mpd, 0x01);
	outb_wait(spd, 0x01);

	// restore masks
	outb(mpd, mmsk);
	outb(spd, smsk);
}

void pic_mask(uint8_t mmsk, uint8_t smsk) {
	// set masks
	outb(mpd, mmsk);
	outb(spd, smsk);
}
