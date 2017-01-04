#include "interrupt.h"
#include "grubinfo.h"
#include "pci.h"
#include "acpi.h"
#include "keyboard.h"

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

	acpi_print_tables((struct rsd_table *)rsdp->rsdt_address);
	
	vga_newline();

	vga_writeln("Scanning PCI devices");

	struct pci_device pdev;
	
	for(u16 bus = 0; bus < 256; bus++) {
		for(u8 dev = 0; dev < 32; dev++) {
			pci_get_info(&pdev,bus,0,dev);
			if(pdev.vendorID != 0xFFFF) {
				pci_print(&pdev);
			}	
		}
	}

	kb_init();

	paging_init();

	vga_write("kernel end address: ");
	vga_writehex((u32)&kernel_end_addr,1);
	vga_newline();

	const char * buf = "TEST TXT";
	char * ptr = 0x0;
	memcpy(ptr,buf,9);

	vga_writeln((char*)0x0);

	hcf();

}
