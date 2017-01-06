#include "shell/shell.h"
#include "core/time.h"

const char * msg = "BOSKI MANNN SALIII DE LA FALOOPAA GILAAA";

u8 boski_main(void) {

	u8 tmp = vga_color;

	u8 color = 9;
	for(u8 i = 0; i < strlen(msg); i++) {

		vga_color = vga_entry_color(color, VGA_COLOR_BLACK);
		vga_writechar(msg[i]);
		waitms(50);
		if(++color == 14)
			color = 9;

	}
	vga_newline();

	vga_color = tmp;
	return 1;

}
