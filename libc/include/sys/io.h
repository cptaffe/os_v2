
#ifndef SYS_IO_H
#define SYS_IO_H

void outb(unsigned short port, unsigned char value);
unsigned short inb(unsigned short port);

void io_wait();

#endif // SYS_IO_H
