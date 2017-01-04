#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "pit.h"
#include "pic.h"
#include "memory.h"
#include "time.h"
#include "vga.h"
#include "keyboard.h"

struct idt_entry {

	u16 offset_low;
	u16 selector;
	u8 reserved;
	u8 flags;
	u16 offset_high;

} __attribute__((packed));

struct idt_ptr {
	
	u16 size;
	u32 offset;

} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtr;

extern void load_idt(void);

void idt_entry_init(u8 index, u32 offset, u16 selector, u8 flags);
void idt_init(void);

extern void inth_0(void);
extern void inth_1(void);
extern void inth_2(void);
extern void inth_3(void);
extern void inth_4(void);
extern void inth_5(void);
extern void inth_6(void);
extern void inth_7(void);
extern void inth_8(void);
extern void inth_9(void);
extern void inth_10(void);
extern void inth_11(void);
extern void inth_12(void);
extern void inth_13(void);
extern void inth_14(void);
extern void inth_15(void);
extern void inth_16(void);
extern void inth_17(void);
extern void inth_18(void);
extern void inth_19(void);
extern void inth_20(void);
extern void inth_21(void);
extern void inth_22(void);
extern void inth_23(void);
extern void inth_24(void);
extern void inth_25(void);
extern void inth_26(void);
extern void inth_27(void);
extern void inth_28(void);
extern void inth_29(void);
extern void inth_30(void);
extern void inth_31(void);

extern void irqh_32(void);
extern void irqh_33(void);
extern void irqh_34(void);
extern void irqh_35(void);
extern void irqh_36(void);
extern void irqh_37(void);
extern void irqh_38(void);
extern void irqh_39(void);
extern void irqh_40(void);
extern void irqh_41(void);
extern void irqh_42(void);
extern void irqh_43(void);
extern void irqh_44(void);
extern void irqh_45(void);
extern void irqh_46(void);
extern void irqh_47(void);

void exception_handler(struct cpu_state * cpu);
void interrupt_handler(struct cpu_state * cpu);

#endif
