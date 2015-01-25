
#include <stdint.h>
#include <stdio.h>
#include <kernel/kbd.h>
#include <sys/io.h>

static kbd_info kbd_main = {
	.ckey_code = 0
};

kbd_info *kbd0 = &kbd_main;

static char kbd_map_lowercase[] = " 1234567890-=\b qwertyuiop[]\n asdfghjkl;'`  zxcvbnm,./     ";

static char kbd_map_uppercase[] = " !@#$%^&*()_+\b QWERTYUIOP[]\n ASDFGHJKL:\"~  ZXCVBNM<>?     ";

void kbd_in(kbd_info *kbd, uint16_t kc) {
	if (kbd->ckey_code != kc) {
		kbd->ckey_code = kc;

		// manage key signal
		if (kc & 0x80) {
			kc ^= 0x80; // kc is now standard key signal
			// key up
			if (kc == 42 || kc == 52) {
				// shift key
				kbd->state = KBD_NSHIFT;
			}
		} else {
			// key down
			if (kc == 42 || kc == 52) {
				// shift key
				kbd->state = KBD_SHIFT;
			} else {
				// key down
				char *map;
				int map_size;
				if (kbd->state & KBD_SHIFT) {
					map = kbd_map_uppercase;
					map_size = sizeof(kbd_map_uppercase);
				} else {
					map = kbd_map_lowercase;
					map_size = sizeof(kbd_map_lowercase);
				}
				if (kc < map_size) {
					putchar(map[kc - 1]);
				} else {
					printf("<%d>", kc);
				}
			}
		}
	}
}

void kbd_int(int keycode) {
	kbd_in(kbd0, keycode);
}
