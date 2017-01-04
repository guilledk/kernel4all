#ifndef _CASM_H_
#define _CASM_H_

#include "types.h"

struct cpu_state { //128 bit(16 byte) structure, cpu regs

	u32 gs, fs, es, ds;
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 int_no, err;
	u32 eip, cs, eflags, useresp, ss;

} __attribute__((packed));

//IO
extern void outb(u16 port, u8 val);
extern void outw(u16 port, u16 val);
extern void outd(u16 port, u32 val);

extern u8 inb(u16 port);
extern u16 inw(u16 port);
extern u32 ind(u16 port);

extern void iowait(void);

//GDT
extern void gdt_init(void);

#endif
