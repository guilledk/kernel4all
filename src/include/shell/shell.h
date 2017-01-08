#ifndef _SHELL_H_
#define _SHELL_H_

#include "interrupts/keyboard.h"

#include "core/types.h"
#include "core/vga.h"
#include "core/string.h"
#include "core/memory.h"

#define SHELL_CSTR_ADDR 0x0
#define SHELL_CSTR_MAXS 256

#define SHELL_CMD_COUNT 5

#define PROG_CSTR_ADDR  (SHELL_CSTR_ADDR + SHELL_CSTR_MAXS)
#define PROG_CSTR_MAXS  256

extern const char * prompt;
extern const char * commands[SHELL_CMD_COUNT];
extern const u8 cmd_lenghts[SHELL_CMD_COUNT];

char * current_str;
u8 current_len;
u8 return_code;

void shell_register_cmd(u8 (*entry_point)(void), u8 index);
void shell_input(void (*callback)(void));
void shell_in(char c);
void shell_prompt(void);
void shell_exec(void);
void shell_init(void);

u8 help_main(void);
u8 clear_main(void);
u8 boski_main(void);
u8 lspci_main(void);
u8 intest_main(void);

#endif
