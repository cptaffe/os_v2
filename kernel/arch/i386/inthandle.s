.align 4

.section .bss
# interrupt struct
.int_struct:
.long $0
.long $0

.section .text

# no error macro definition
.macro INT_HANDLE_NOERR num
.global int_handler_\num
int_handler_\num:
	cli
	pusha
	movl $0, .int_struct
	movl $\num, .int_struct + 4
	jmp .int_all
.endm

# error macro definition
.macro INT_HANDLE_ERR num
.global int_handler_\num
int_handler_\num:
	cli
	pusha
	pop %eax
	movl %eax, .int_struct
	movl $\num, .int_struct + 4
	jmp .int_all
.endm

INT_HANDLE_NOERR 0
INT_HANDLE_NOERR 1
INT_HANDLE_NOERR 2
INT_HANDLE_NOERR 3
INT_HANDLE_NOERR 4
INT_HANDLE_NOERR 5
INT_HANDLE_NOERR 6
INT_HANDLE_NOERR 7
INT_HANDLE_ERR 8
INT_HANDLE_NOERR 9
INT_HANDLE_ERR 10
INT_HANDLE_ERR 11
INT_HANDLE_ERR 12
INT_HANDLE_ERR 13
INT_HANDLE_ERR 14
INT_HANDLE_NOERR 15
INT_HANDLE_NOERR 16
INT_HANDLE_NOERR 17
INT_HANDLE_NOERR 18
INT_HANDLE_NOERR 19
INT_HANDLE_NOERR 20
INT_HANDLE_NOERR 21
INT_HANDLE_NOERR 22
INT_HANDLE_NOERR 23
INT_HANDLE_NOERR 24
INT_HANDLE_NOERR 25
INT_HANDLE_NOERR 26
INT_HANDLE_NOERR 27
INT_HANDLE_NOERR 28
INT_HANDLE_NOERR 29
INT_HANDLE_NOERR 30
INT_HANDLE_NOERR 31
INT_HANDLE_NOERR 32
INT_HANDLE_NOERR 33
INT_HANDLE_NOERR 34
INT_HANDLE_NOERR 35
INT_HANDLE_NOERR 36
INT_HANDLE_NOERR 37
INT_HANDLE_NOERR 38
INT_HANDLE_NOERR 39
INT_HANDLE_NOERR 40

# does actual handler call
.int_all:
	# set up stack for call
	push %ebp
	mov %esp, %ebp

	# call & cleanup stack
	push $.int_struct
	push $kern0
	call int_handler
	add $8, %esp
	pop %ebp

	# retrieve state, turn interrupts on, and return
	popa
	sti
	iret
