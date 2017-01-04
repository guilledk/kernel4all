#include "interrupt.h"

void idt_entry_init(u8 index, u32 offset, u16 selector, u8 flags) {

	idt[index].offset_low = (offset & 0xFFFF);
	idt[index].selector = selector;
	idt[index].reserved = 0;
	idt[index].flags = flags;
	idt[index].offset_high = (offset & 0xFFFF0000) >> 16;	

}

void idt_init(void) {

	memset((u8*)&idt, 0, sizeof(struct idt_entry) * 256);

	idt_entry_init(0,(u32)inth_0,0x08,0x8E);
	idt_entry_init(1,(u32)inth_1,0x08,0x8E);
	idt_entry_init(2,(u32)inth_2,0x08,0x8E);
	idt_entry_init(3,(u32)inth_3,0x08,0x8E);
	idt_entry_init(4,(u32)inth_4,0x08,0x8E);
	idt_entry_init(5,(u32)inth_5,0x08,0x8E);
	idt_entry_init(6,(u32)inth_6,0x08,0x8E);
	idt_entry_init(7,(u32)inth_7,0x08,0x8E);
	idt_entry_init(8,(u32)inth_8,0x08,0x8E);
	idt_entry_init(9,(u32)inth_9,0x08,0x8E);
	idt_entry_init(10,(u32)inth_10,0x08,0x8E);
	idt_entry_init(11,(u32)inth_11,0x08,0x8E);
	idt_entry_init(12,(u32)inth_12,0x08,0x8E);
	idt_entry_init(13,(u32)inth_13,0x08,0x8E);
	idt_entry_init(14,(u32)inth_14,0x08,0x8E);
	idt_entry_init(15,(u32)inth_15,0x08,0x8E);
	idt_entry_init(16,(u32)inth_16,0x08,0x8E);
	idt_entry_init(17,(u32)inth_17,0x08,0x8E);
	idt_entry_init(18,(u32)inth_18,0x08,0x8E);
	idt_entry_init(19,(u32)inth_19,0x08,0x8E);
	idt_entry_init(20,(u32)inth_20,0x08,0x8E);
	idt_entry_init(21,(u32)inth_21,0x08,0x8E);
	idt_entry_init(22,(u32)inth_22,0x08,0x8E);
	idt_entry_init(23,(u32)inth_23,0x08,0x8E);
	idt_entry_init(24,(u32)inth_24,0x08,0x8E);
	idt_entry_init(25,(u32)inth_25,0x08,0x8E);
	idt_entry_init(26,(u32)inth_26,0x08,0x8E);
	idt_entry_init(27,(u32)inth_27,0x08,0x8E);
	idt_entry_init(28,(u32)inth_28,0x08,0x8E);
	idt_entry_init(29,(u32)inth_29,0x08,0x8E);
	idt_entry_init(30,(u32)inth_30,0x08,0x8E);
	idt_entry_init(31,(u32)inth_31,0x08,0x8E);

	idt_entry_init(32,(u32)irqh_32,0x08,0x8F);
	idt_entry_init(33,(u32)irqh_33,0x08,0x8F);
	idt_entry_init(34,(u32)irqh_34,0x08,0x8F);
	idt_entry_init(35,(u32)irqh_35,0x08,0x8F);
	idt_entry_init(36,(u32)irqh_36,0x08,0x8F);
	idt_entry_init(37,(u32)irqh_37,0x08,0x8F);
	idt_entry_init(38,(u32)irqh_38,0x08,0x8F);
	idt_entry_init(39,(u32)irqh_39,0x08,0x8F);
	idt_entry_init(40,(u32)irqh_40,0x08,0x8F);
	idt_entry_init(41,(u32)irqh_41,0x08,0x8F);
	idt_entry_init(42,(u32)irqh_42,0x08,0x8F);
	idt_entry_init(43,(u32)irqh_43,0x08,0x8F);
	idt_entry_init(44,(u32)irqh_44,0x08,0x8F);
	idt_entry_init(45,(u32)irqh_45,0x08,0x8F);
	idt_entry_init(46,(u32)irqh_46,0x08,0x8F);
	idt_entry_init(47,(u32)irqh_47,0x08,0x8F);
	
	pic_remap();

	pit_init();

	idtr.size = (sizeof (struct idt_entry) * 256) - 1;
	idtr.offset = (u32)&idt;

	load_idt();

	ticks = 0;

}

void exception_handler(struct cpu_state * cpu) {
	char buf[8];
	itoa(buf, cpu->int_no, 10);
	vga_write("Exception ");
	vga_write(buf);
	vga_write(" called! Error code: ");
	itoa(buf, cpu->err, 10);
	vga_write(buf);
	vga_newline();

	for(;;);
}

void interrupt_handler(struct cpu_state * cpu) {

	switch(cpu->int_no) {
		case 32 : {
			ticks++;
			break;
		}
		case 33 : {
			u8 scancode = inb(0x60);
			kb_in(scancode);
			break;
		}
		default : {
			char buf[8];
			itoa(buf, cpu->int_no, 10);
			vga_write("Interrupt ");
			vga_write(buf);
			vga_write(" called.\n");
			break;
		}
	}

	pic_acknowledge(cpu->int_no + 0x20);
}
