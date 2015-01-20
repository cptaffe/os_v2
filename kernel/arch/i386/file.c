
#include <kernel/file.h>
#include <kernel/tty.h>

static tty tty_out; // default output via tty
static file file_out; // default file out
file *stdout;

// constructor runs on boot
__attribute__((constructor))
void init_glbl_file() {
	stdout = &file_out;
	file_open(stdout, FILE_TTY, &tty_out);
}

file *file_open(file *file, enum file_type type, void *out) {
	file->type = type;
	file->out = out;

	// init action for file type
	if (type == FILE_TTY) {
		tty_init((tty *) out);
	}

	return file;
}

size_t file_write(file *f, void *mem, size_t size) {
	if (f->type == FILE_TTY) {
		return tty_write((tty *) f->out, mem, size);
	} else {
		return 0; // cannot write yet.
	}
}


size_t file_read(file *f, void *mem, size_t size) {
	return 0; // cannot read yet.
}