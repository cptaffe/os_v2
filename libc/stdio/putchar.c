
#include <stdio.h>

#if defined(__is_myos_kernel)
#include <kernel/file.h>
#endif

int putchar(int ic) {
#if defined(__is_myos_kernel)
	file_write(stdout, &ic, 1);
#else
	// TODO: You need to implement a write system call.
#endif
	return ic;
}
