
# Copyright (c) 2015 Connor Taffe <cpaynetaffe@gmail.com>

.section .text

# hang function
.global hang
.type hang, @function
hang:
	# hang (by halting core)
	# note: interrupts are not off.
	hlt
	.hang:
	jmp .hang
