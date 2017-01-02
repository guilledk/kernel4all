#include "vga.h"
#include "casm.h"

void hcf(void) { //Halt And Catch Fire

	for(;;);

}

void kernel_main(void) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1");

	gdt_init();

	hcf();

}
