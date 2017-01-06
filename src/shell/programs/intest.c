#include "shell/shell.h"

void endstr(void) {

	vga_writeln(current_str);

}

u8 intest_main(void) {

	vga_write("input: ");
	shell_input(endstr);
	return 0;

}
