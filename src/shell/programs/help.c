#include "shell/shell.h"

const char * help_txt = "Kernel 4 All shell v1 commands:";

u8 help_main(void) {

	vga_writeln(help_txt);
	for(u8 i = 0; i < SHELL_CMD_COUNT - 1; i++) {

		vga_write(commands[i]);
		vga_write(", ");

	}
	vga_writeln(commands[SHELL_CMD_COUNT - 1]);
	return 1;

}
