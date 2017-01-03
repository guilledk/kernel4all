#include "grubinfo.h"

void get_info(multiboot_info_t * mbd) {
	vga_write("Booted by: ");
	if(bit(mbd->flags,9))
		vga_writeln((char *)mbd->boot_loader_name);
	char buffer[32];
	itoa(buffer,(mbd->mem_lower + mbd->mem_upper) / 1024, 10);
	vga_write("Memory: ");
	vga_write(buffer);
	vga_writeln("MB");
}

void get_infofull(multiboot_info_t * mbd) {

	char buffer[32];

	vga_write("Booted by: ");
	if(bit(mbd->flags,9))
		vga_writeln((char *)mbd->boot_loader_name);

	itoa(buffer,mbd->mem_lower, 10);
	vga_write("Lower Memory: ");
	vga_write(buffer);
	vga_writeln("KB");
	itoa(buffer,mbd->mem_upper, 10);
	vga_write("Upper Memory: ");
	vga_write(buffer);
	vga_writeln("KB");
	itoa(buffer,(mbd->mem_lower + mbd->mem_upper) / 1024, 10);
	vga_write("Total Memory: ");
	vga_write(buffer);
	vga_writeln("MB");

	vga_write("\n\nFlags: ");
	for(int i = 12; i >= 0; i--) {
		u8 b = bit(mbd->flags,i);
		itoa(buffer,b,10);

		vga_write(buffer);
		vga_write(", ");

		u8 tmpx, tmpy;
		tmpx = vga_x;
		tmpy = vga_y;

		itoa(buffer,i,10);
		vga_x -= 3;
		vga_y--;
		vga_write(buffer);
		vga_x = tmpx;
		vga_y = tmpy;
	}
	vga_newline();
	vga_newline();

	if(bit(mbd->flags,0))
		vga_writeln("\tMemory information available.");
	if(bit(mbd->flags,1))
		vga_writeln("\tBoot device information available.");
	if(bit(mbd->flags,2))
		vga_writeln("\tCMDLine information available.");
	if(bit(mbd->flags,3))
		vga_writeln("\tModule information available.");
	if(bit(mbd->flags,4) || bit(mbd->flags,5))
		vga_writeln("\tSymbol information available.");
	if(bit(mbd->flags,6))
		vga_writeln("\tMemory map available.");
	if(bit(mbd->flags,7))
		vga_writeln("\tDrive information available.");
	if(bit(mbd->flags,8))
		vga_writeln("\tConfig Table information available.");
	if(bit(mbd->flags,9))
		vga_writeln("\tBoot loader name available.");
	if(bit(mbd->flags,10))
		vga_writeln("\tAPM Table information available.");
	if(bit(mbd->flags,11))
		vga_writeln("\tVBE information available.");

}
