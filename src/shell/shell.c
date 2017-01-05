#include "shell.h"

const char * prompt = "-> ";

const char * commands[SHELL_CMD_COUNT] = {

	"help",
	"boski",
	"lspci"

};

void shell_in(char c) {
	if(current_len == 255)
		return;

	switch(c) {
		case '\b' : {
			if(current_len == 0)
				return;
			current_len--;
			vga_backspace();
			break;
		}
		case '\n' : {
			kb_set_enabled(0);
			vga_newline();
			shell_exec();
			break;
		}
		default : {
			*(current_str + current_len) = c;
			current_len++;
			vga_writechar(c);
			break;
		}
	}
}

void shell_prompt(void) {
	vga_write(prompt);
	kb_set_enabled(1);
}

void shell_exec(void) {
	vga_writeln("OK.");
	shell_prompt();
}

void shell_init(void) {
	
	inchar = shell_in;

	current_str = SHELL_CSTR_ADDR;
	current_len = 0;

	shell_prompt();

}
