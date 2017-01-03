#include "vga.h"

void vga_init(void) {

	vga_buf = (u16 *) 0xB8000;
	vga_empty = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	vga_clear();

	//Disable text mode cursor
	u8 io_status = inb(0x3CC);
	if(bit(io_status,0)) {
		outb(0x3D4,0x0A);
		iowait();
		u8 csr = inb(0x3D5);
		outb(0x3D5, csr | 0b00100000);
	} else {
		outb(0x3B4,0x0A);
		iowait();
		u8 csr = inb(0x3B5);
		outb(0x3B5, csr | 0b00100000);
	}	

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

void vga_writeln(const char * str) {
	vga_write(str);
	vga_newline();
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

void vga_splash(u8 x, u8 y) {

	const u16 filled = vga_entry(' ',vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_GREEN));

	vga_putat(filled,x+1,y);
	vga_putat(filled,x+4,y);
	vga_putat(filled,x+5,y);
	vga_putat(filled,x+6,y);
	vga_putat(filled,x+7,y);
	vga_putat(filled,x+10,y);

	vga_putat(filled,x,y+1);
	vga_putat(filled,x+3,y+1);
	vga_putat(filled,x+8,y+1);
	vga_putat(filled,x+11,y+1);

	vga_putat(filled,x+2,y+2);
	vga_putat(filled,x+9,y+2);

	vga_putat(filled,x+1,y+3);
	vga_putat(filled,x+4,y+3);
	vga_putat(filled,x+7,y+3);
	vga_putat(filled,x+10,y+3);

	vga_putat(filled,x+1,y+4);
	vga_putat(filled,x+5,y+4);
	vga_putat(filled,x+6,y+4);
	vga_putat(filled,x+10,y+4);
	
	vga_putat(filled,x+1,y+5);
	vga_putat(filled,x+4,y+5);
	vga_putat(filled,x+7,y+5);
	vga_putat(filled,x+10,y+5);

	vga_putat(filled,x+2,y+6);
	vga_putat(filled,x+9,y+6);

	vga_putat(filled,x,y+7);
	vga_putat(filled,x+3,y+7);
	vga_putat(filled,x+8,y+7);
	vga_putat(filled,x+11,y+7);

	vga_putat(filled,x+1,y+8);
	vga_putat(filled,x+4,y+8);
	vga_putat(filled,x+5,y+8);
	vga_putat(filled,x+6,y+8);
	vga_putat(filled,x+7,y+8);
	vga_putat(filled,x+10,y+8);
	

}
