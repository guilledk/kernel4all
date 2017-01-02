#ifndef _CASM_H_
#define _CASM_H_

#include "types.h"

//IO
extern void outb(u16 port, u8 val);
extern void inb(u16 port);

//GDT
extern void gdt_init(void);

#endif
