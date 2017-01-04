#include "pic.h"

void pic_acknowledge(u32 interrupt) {

	if (interrupt >= PIC2_START_INTERRUPT)
		outb(PIC2_COMMAND, PIC_ACK);

	outb(PIC1_COMMAND, PIC_ACK);

}

void pic_remap(void) {

	u8 a1, a2;
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	iowait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	iowait();
	outb(PIC1_DATA, PIC1_START_INTERRUPT);    // ICW2: Master PIC vector offset
	iowait();
	outb(PIC2_DATA, PIC2_START_INTERRUPT);    // ICW2: Slave PIC vector offset
	iowait();
	outb(PIC1_DATA, 4);
	iowait();
	outb(PIC2_DATA, 2);
	iowait();

	outb(PIC1_DATA, ICW4_8086);
	iowait();
	outb(PIC2_DATA, ICW4_8086);
	iowait();

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);

}
