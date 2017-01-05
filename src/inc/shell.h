#ifndef _SHELL_H_
#define _SHELL_H_

#include "types.h"
#include "keyboard.h"
#include "vga.h"

#define SHELL_CSTR_ADDR 0x0;
#define SHELL_CSTR_MAXS 256; 

#define SHELL_CMD_COUNT 3

extern const char * prompt;
extern const char * commands[SHELL_CMD_COUNT];

char * current_str;
u8 current_len;

void shell_in(char c);
void shell_prompt(void);
void shell_exec(void);
void shell_init(void);

#endif
