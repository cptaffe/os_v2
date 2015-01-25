
#include <kernel/syscall.h>
#include <kernel/kernel.h>
#include <stdio.h>

const uint8_t syscall_num = 0x80;

// underlying syscall signature
int32_t os_syscall(kernel *kern, uint32_t num, uint32_t args[]) {
	printf("I am syscall #%d\n", (int) num);
	printf("First argument is %d\n", (int) args[0]);
	return num;
}
