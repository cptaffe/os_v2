# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:

	# set up protected mode lgtr
	#cli
	#lgdt (gdtr)

	call bootstrap_64

	# init stack
	movl $stack_top, %esp

	# init core kernel, called with kern0
	mov kern0, %eax
	pushl %eax
	call kernel_early

	# call global constructors in the .init section
	# _fini for .fini is also avaliable.
	call _init

	# main kernel, called with kern0
	mov kern0, %eax
	pushl %eax
	call kernel_main

.size _start, . - _start

# setup global descriptor table
# sets permissions on segments & useful for kernel.
gdtr:
.word (gdt_end - gdt) + 1
.long gdt

gdt:
# null entry
.quad 0
# code entry
.word 0xffff
.word 0x0000
.byte 0x00
.byte 0b10011010
.byte 0x4f
.byte 0x00
# data entry
.word 0xffff
.word 0x0000
.byte 0x00
.byte 0b10010010
.byte 0x4f
.byte 0x00

gdt_end:

.fill 510-(.-gdt_end), 1, 0
.byte 0x55
.byte 0xaa
