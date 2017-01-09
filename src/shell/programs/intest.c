#include "shell/shell.h"

char * str;
u8 clen;

void input(char c) {
	if(clen == PROG_CSTR_MAXS - 1 && c != '\b' && c != '\n')
		return;

	switch(c) {
		case '\b' : {
			if(clen == 0)
				return;
			*(str + clen) = 0;
			clen--;
			vga_backspace();
			break;
		}
		case '\n' : {
			kb_set_enabled(0);
			vga_newline();
			vga_writeln(str);
			shell_prompt();
			break;
		}
		default : {
			*(str + clen) = c;
			*(str + clen + 1) = 0;
			clen++;
			vga_writechar(c);
			break;
		}
	}
}

u8 intest_main(void) {

	clen = 0;
	str = (char *)PROG_CSTR_ADDR;
	vga_write("input: ");
	inchar = input;
	kb_set_enabled(1);
	return 0;

}
