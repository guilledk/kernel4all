#include "pit.h"

void pit_init(void) {

	u16 divisor = 1193180 / 100;
	
	outb(0x43,0b110110); //send command

	outb(0x40, (u8)(divisor & 0xFF));		//Send low byte
	outb(0x40, (u8)((divisor & 0xFF00) >> 8));	//Send high byte

}
