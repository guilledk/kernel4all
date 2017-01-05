#include "shell/shell.h"

const char * prompt = "-> ";

const char * commands[SHELL_CMD_COUNT] = {

	"help",
	"clear",
	"boski",
	"lspci"

};

const u8 cmd_lenghts[SHELL_CMD_COUNT] = {
	
	4,
	5,
	5,
	5

};

void (*entry_points[SHELL_CMD_COUNT])(void) = {

	0, 0, 0, 0

};

void shell_register_cmd(void (*entry_point)(void), u8 index) {

	entry_points[index] = entry_point;

}

void shell_in(char c) {
	if(current_len == SHELL_CSTR_MAXS - 1 && c != '\b' && c != '\n')
		return;

	switch(c) {
		case '\b' : {
			if(current_len == 0)
				return;
			*(current_str + current_len) = 0;
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
			*(current_str + current_len + 1) = 0;
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
	
	u8 found = 0;
	for(u8 i = 0; i < SHELL_CMD_COUNT; i++) {
		if(current_len == cmd_lenghts[i]) {
			if(memcmp((u8*)current_str,(u8*)commands[i],current_len)) {
				found = 1;
				if(entry_points[i]) {
					(*entry_points[i])();
				}
			}
		}
	}
	if(!found)
		vga_writeln("Command not found! try \"help\".");

	*current_str = 0;
	current_len = 0;
	
	shell_prompt();
}

void shell_init(void) {
	
	inchar = shell_in;

	current_str = SHELL_CSTR_ADDR;
	*current_str = 0;
	current_len = 0;

	shell_register_cmd(help_main, 0);
	shell_register_cmd(vga_clear, 1);
	shell_register_cmd(boski_main,2);
	shell_register_cmd(lspci_main,3);

	shell_prompt();

}
