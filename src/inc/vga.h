#ifndef _VGA_H_
#define _VGA_H_

#include "types.h"
#include "string.h"

typedef enum vga_color {

	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,

} vcolor;

static const u8 VGA_WIDTH = 80;
static const u8 VGA_HEIGHT = 25;
static const u8 VGA_TAB_SIZE = 4;

u16 vga_empty;
u16 * vga_buf;
u8 vga_x;
u8 vga_y;
u8 vga_color;

void vga_init(void);

u8 vga_entry_color(vcolor fg, vcolor bg);
u16 vga_entry(u8 uchar, u8 ecolor);

void vga_clear(void);
void vga_putat(u16 entry, u8 x, u8 y);
void vga_write(const char * str);
void vga_newline(void);

void vga_splash(const char * boot_msg);

#endif
