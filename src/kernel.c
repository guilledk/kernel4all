#include "interrupt.h"

//Halt And Catch Fire
void hcf(void) { for(;;); }

void kernel_main(void) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1\n");

	gdt_init();

	idt_init();

	hcf();

}
