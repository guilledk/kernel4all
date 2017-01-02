#include "vga.h"

void vga_init(void) {

	vga_buf = (u16 *) 0xB8000;
	vga_empty = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	vga_clear();

}

u8 vga_entry_color(vcolor fg, vcolor bg) {

	return fg | bg << 4;

}

u16 vga_entry(u8 uchar, u8 ecolor) {

	return (u16)uchar | (u16)ecolor << 8;

}

void vga_clear(void) {
	vga_x = 0;
	vga_y = 0;
	vga_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (u8 y = 0; y < VGA_HEIGHT; y++) {
		for (u8 x = 0; x < VGA_WIDTH; x++) {
			vga_putat(vga_empty,x,y);
		}
	}
}

void vga_putat(u16 entry, u8 x, u8 y) {
	
	const u16 index = y * VGA_WIDTH + x;
	vga_buf[index] = entry;

}

void vga_write(const char * str) {

	while(*str) {
		if(*str == '\n') {
			vga_newline();
			str++;
			continue;
		}
		if(*str == '\t') {
			u8 n = VGA_TAB_SIZE;
			while(n--) {
				vga_putat(vga_entry(' ', vga_color),vga_x,vga_y);
				vga_x++;
			}
			str++;
			continue;
		}
		u16 entry = vga_entry(*str,vga_color);
		vga_putat(entry, vga_x, vga_y);
		if(++vga_x == VGA_WIDTH)
			vga_newline();
		str++;
	}

}

void vga_newline(void) {

	vga_x = 0;
	if(++vga_y == VGA_HEIGHT) {
		for (u8 y = 1; y < VGA_HEIGHT; y++) {
			for (u8 x = 0; x < VGA_WIDTH; x++) {
				const u16 pindex = (y - 1) * VGA_WIDTH + x;
				const u16 index = y * VGA_WIDTH + x;
				vga_buf[pindex] = vga_buf[index];
			}
		}
		for (u8 x = 0; x < VGA_WIDTH; x++) {
			const u16 index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
			vga_buf[index] = vga_empty;;
		}
		vga_y--;
	}

}

void vga_splash(const char * boot_msg) {

	u16 empty  = vga_entry(' ',vga_entry_color(VGA_COLOR_BLACK,VGA_COLOR_BLACK));
	u16 filled = vga_entry(' ',vga_entry_color(VGA_COLOR_WHITE,VGA_COLOR_WHITE));

	u8 x_offset = (VGA_WIDTH / 2) - 4;
	u8 y_offset = (VGA_HEIGHT / 2) - 2;

	vga_putat(empty, x_offset + 0, y_offset + 0);
	vga_putat(filled, x_offset + 1, y_offset + 0);
	vga_putat(filled, x_offset + 2, y_offset + 0);
	vga_putat(empty, x_offset + 3, y_offset + 0);
	vga_putat(filled, x_offset + 4, y_offset + 0);
	vga_putat(filled, x_offset + 5, y_offset + 0);
	vga_putat(filled, x_offset + 6, y_offset + 0);
	vga_putat(empty, x_offset + 7, y_offset + 0);

	vga_putat(empty, x_offset + 0, y_offset + 1);
	vga_putat(filled, x_offset + 1, y_offset + 1);
	vga_putat(filled, x_offset + 2, y_offset + 1);
	vga_putat(empty, x_offset + 3, y_offset + 1);
	vga_putat(empty, x_offset + 4, y_offset + 1);
	vga_putat(filled, x_offset + 5, y_offset + 1);
	vga_putat(filled, x_offset + 6, y_offset + 1);
	vga_putat(empty, x_offset + 7, y_offset + 1);

	vga_putat(empty, x_offset + 0, y_offset + 2);
	vga_putat(filled, x_offset + 1, y_offset + 2);
	vga_putat(filled, x_offset + 2, y_offset + 2);
	vga_putat(filled, x_offset + 3, y_offset + 2);
	vga_putat(empty, x_offset + 4, y_offset + 2);
	vga_putat(filled, x_offset + 5, y_offset + 2);
	vga_putat(empty, x_offset + 6, y_offset + 2);
	vga_putat(empty, x_offset + 7, y_offset + 2);

	vga_x = (VGA_WIDTH / 2) - (strlen(boot_msg) / 2);
	vga_y = (VGA_HEIGHT / 2) + 2;
	vga_write(boot_msg);

}
