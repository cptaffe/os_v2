.section .init
	# gcc puts crtend.o's .init here
	popl %ebp
	ret

.section .fini
	# gcc puts crtend.o's .fini here
	popl %ebp
	ret
