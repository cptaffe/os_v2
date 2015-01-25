
// Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

#ifndef KERNEL_SYSCALL_H_
#define KERNEL_SYSCALL_H_

#include <stdint.h>

extern const uint8_t syscall_num;

// takes syscall interrupt #
int32_t check_syscall();

#endif // KERNEL_SYSCALL_H_
