#include "interrupt.h"
#include "grubinfo.h"

//Halt And Catch Fire
void hcf(void) { for(;;); }

void kernel_main(multiboot_info_t * mbd) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1\n");

	gdt_init();

	idt_init();

	get_infofull(mbd);

	//vga_newline();
	//vga_splash(0,vga_y);
	//vga_y += 9;
	//vga_write("\nButia\n");

	hcf();

}
