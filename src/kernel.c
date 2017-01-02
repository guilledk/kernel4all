#include "vga.h"

void hcf(void) {

	for(;;);

}

void kernel_main(void) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1");

	hcf();

}
