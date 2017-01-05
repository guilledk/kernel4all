#ifndef _SHELL_H_
#define _SHELL_H_

#include "core/types.h"
#include "interrupts/keyboard.h"
#include "core/vga.h"
#include "core/string.h"
#include "core/memory.h"

#define SHELL_CSTR_ADDR 0x0
#define SHELL_CSTR_MAXS 256

#define SHELL_CMD_COUNT 4

extern const char * prompt;
extern const char * commands[SHELL_CMD_COUNT];
extern const u8 cmd_lenghts[SHELL_CMD_COUNT];

char * current_str;
u8 current_len;

void shell_register_cmd(void (*entry_point)(void), u8 index);
void shell_in(char c);
void shell_prompt(void);
void shell_exec(void);
void shell_init(void);

void help_main(void);
void clear_main(void);
void boski_main(void);
void lspci_main(void);

#endif
