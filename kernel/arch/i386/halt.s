
# Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

.section .text

# hang function
.global hang
.type hang, @function
hang:
	# Hang if kernel_main unexpectedly returns.
	cli
	hlt
	.hang:
	jmp .hang
