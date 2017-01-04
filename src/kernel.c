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
	const char * buf = "RSD PTR ";
	if(memcmp((u8*)buf,rsdp->signature,8)){
		vga_writeln("Root System Description Pointer Found!");
		char rev[8];
		itoa(rev,rsdp->rev,10);
		vga_write("\trev: ");
		vga_writeln(rev);
		
	}

	struct pci_device dev;
	pci_get_info(&dev,0,0,0);
	pci_print(&dev);

	hcf();

}
