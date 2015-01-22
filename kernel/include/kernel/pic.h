
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_PIC_H_
#define KERNEL_PIC_H_

#include <stddef.h>
#include <stdint.h>

void pic_init(uint8_t off1, uint8_t off2);
void pic_mask(uint8_t mmask, uint8_t smask);
void pic_eoi(uint8_t irq);

#endif // KERNEL_PIC_H_
