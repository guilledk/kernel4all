#include "vga.h"

void vga_init(void) {

	vga_buf = (u16 *) 0xB8000;
	vga_empty = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	vga_clear();

	/*
	  Disable text mode cursor
	  http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A

	  Read Miscellaneous Output Register (Read at 3CCh, Write at 3C2h)
	  This bit selects the CRT controller addresses.

	  When set to 0, this bit sets the CRT controller addresses 
	  to 0x03Bx and the address for the Input Status Register 1
	  to 0x03BA for compatibility with the monochrome adapter.

	  When set to 1, this bit sets CRT controller addresses to 0x03Dx
	  and the Input Status Register 1 address to 0x03DA for compatibility
	  with the color/graphics adapter.
	*/
	u8 io_status = inb(0x3CC);
	if(bit(io_status,0)) {
		outb(0x3D4,0x0A); //Set register index to 0x0A
		iowait();
		u8 csr = inb(0x3D5); //Read previous bit field
		iowait();
		outb(0x3D5, csr | 0b00100000); //Set Cursor Disable to true
	} else {
		outb(0x3B4,0x0A);
		iowait();
		u8 csr = inb(0x3B5);
		iowait();
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

void vga_writeuint(u32 num) {

	u32 og = num;
	u32 num_of_digits = 1;
	while(num /= 10) num_of_digits++;
	num = og;

	char number[num_of_digits + 1];
	for(i8 i = num_of_digits - 1; i >= 0; i--) {
		number[i] = 48 + (num % 10);
		num /= 10;
	}
	number[num_of_digits] = 0;

	vga_write((char*)number);
}

void vga_writehex(u32 num, u8 upper) {

	u8 hex_digits[8]; 
	hex_digits[0] = (num & 0x0000000F);
	hex_digits[1] = (num & 0x000000F0) >> 4;
	hex_digits[2] = (num & 0x00000F00) >> 8;
	hex_digits[3] = (num & 0x0000F000) >> 12;
	hex_digits[4] = (num & 0x000F0000) >> 16;
	hex_digits[5] = (num & 0x00F00000) >> 20;
	hex_digits[6] = (num & 0x0F000000) >> 24;
	hex_digits[7] = (num & 0xF0000000) >> 28;

	u8 offset = 0;
	if(!upper)
		offset = 32;

	u8 found_digit = 0;

	for(i8 i = 7; i >= 0; i--) {

		if(!found_digit && hex_digits[i] == 0 && i != 0)
			continue;

		found_digit = 1;
		if(hex_digits[i] < 0xA) {
			char digit[2] = { 48 + hex_digits[i], 0 };
			vga_write(digit);
			continue;
		}
		char digit[2] = { 65 + (hex_digits[i] - 0xA) + offset, 0 };
		vga_write(digit);

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
