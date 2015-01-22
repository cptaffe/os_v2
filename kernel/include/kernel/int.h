
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_INT_H_
#define KERNEL_INT_H_

#include <stdint.h>

typedef struct {
	uint32_t err;
	uint32_t num;
} __attribute__((__packed__)) int_info;

void int_keyboard();

void int_handler_0();
void int_handler_1();
void int_handler_2();
void int_handler_3();
void int_handler_4();
void int_handler_5();
void int_handler_6();
void int_handler_7();
void int_handler_8();
void int_handler_9();
void int_handler_10();
void int_handler_11();
void int_handler_12();
void int_handler_13();
void int_handler_14();
void int_handler_15();
void int_handler_16();
void int_handler_17();
void int_handler_18();
void int_handler_19();
void int_handler_20();
void int_handler_21();
void int_handler_22();
void int_handler_23();
void int_handler_24();
void int_handler_25();
void int_handler_26();
void int_handler_27();
void int_handler_28();
void int_handler_29();
void int_handler_30();
void int_handler_31();
void int_handler_32();
void int_handler_33();
void int_handler_34();
void int_handler_35();
void int_handler_36();
void int_handler_37();
void int_handler_38();
void int_handler_39();
void int_handler_40();

#endif // KERNEL_INT_H_
