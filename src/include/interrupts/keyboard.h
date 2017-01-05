#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "core/types.h"

#define KB_ENABLED 0x01
#define KB_INITZED 0x02

u8 kbflags;
void (*inchar)(char);

extern char kbdus[128];

void kb_init(void);
void kb_set_enabled(u8 enabled);
void kb_in(u8 scode);

#endif
