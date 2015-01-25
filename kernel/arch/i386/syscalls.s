
.align 4

.section .text

.global check_syscall
check_syscall:

	// test that 120 was gotten
	push $300
	push $70
	int $0x80
	add $8, %esp
	cmp $70, %eax
	jne .fail
	mov $1, %eax
	ret
.fail:
	mov $0, %eax
	ret
