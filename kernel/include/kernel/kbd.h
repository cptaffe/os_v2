
#ifndef KERNEL_KBD_H_
#define KERNEL_KBD_H_

// bit mask
enum kbd_state {
	KBD_NSHIFT = 0x0 << 0,
	KBD_SHIFT = 0x1 << 0,
	KBD_NCTRL = 0x0 << 1,
	KBD_CTRL = 0x1 << 1,
	KBD_NALT = 0x0 << 1,
	KBD_ALT = 0x1 << 1,
};

typedef struct {
	int ckey_code;
	enum kbd_state state;
	char *key_map;
} kbd_info;

extern kbd_info *kbd0;

void kbd_in(kbd_info *kbd, uint16_t kc);
void kbd_int(int keycode);

#endif // KERNEL_KBD_H_
