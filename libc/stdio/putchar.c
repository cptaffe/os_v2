
#include <stdio.h>

#if defined(__is_myos_kernel)
#include <kernel/tty.h>
#endif

// character buffer, empties on newline.
char buf[1024];
unsigned long long int buffered = 0;

int putchar(int ic) {
#if defined(__is_myos_kernel)
	buf[buffered++] = (char) ic;
	if (ic == '\n' || buffered == 1024) {
		tty_write(&tty_out, buf, buffered);
		buffered = 0;
	}
#else
	// TODO: You need to implement a write system call.
#endif
	return ic;
}
