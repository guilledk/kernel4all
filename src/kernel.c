#include "interrupt.h"
#include "grubinfo.h"
#include "pci.h"
#include "acpi.h"

//Halt And Catch Fire
void hcf(void) { for(;;); }

void kernel_main(multiboot_info_t * mbd) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1\n");

	gdt_init();

	idt_init();

	get_info(mbd);

	struct rsd_ptr * rsdp = acpi_get_rsdp();
	if(rsdp != 0){
		vga_writeln("Root System Description Pointer Found!");
		char rev[8];
		itoa(rev,rsdp->rev,10);
		vga_write("\trev: ");
		vga_writeln(rev);
		if(rsdp->rev > 0) {
			itoa(rev,((struct rsd_ptr_v2 *)rsdp)->len,10);
			vga_write("\tRSDT len: ");
			vga_writeln(rev);
		}
		
	}
	
	vga_newline();

	struct pci_device dev;
	pci_get_info(&dev,0,0,0);
	pci_print(&dev);

	hcf();

}
