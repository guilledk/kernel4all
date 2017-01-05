#include "shell/shell.h"
#include "hardware/pci.h"

void lspci_main(void) {

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

}
