#include "shell/shell.h"
#include "hardware/pci.h"
#include "core/time.h"

u8 lspci_main(void) {

	vga_writeln("Scanning PCI devices");

	u32 start_ticks = ticks;

	struct pci_device_info pdev;
	
	for(u16 bus = 0; bus < 256; bus++) {
		for(u8 dev = 0; dev < 32; dev++) {

			u32 base_id = PCI_MAKE_ID(bus,dev,0);

			u8 head_type = pci_inb(base_id, PCI_CONFIG_HEADER_TYPE);

			if(head_type & PCI_TYPE_MULTIFUNC) {

				for(u8 func = 0; func < 8; func++) {
					pci_get_info(&pdev,bus,dev,func);
					if(pdev.vendorID != 0xFFFF) {
						pci_print(&pdev,bus,dev,func);
					}
				}

			} else {

				pci_get_info(&pdev,bus,dev,0);
				if(pdev.vendorID != 0xFFFF) {
					pci_print(&pdev,bus,dev,0);
				}

			}
		}
	}

	u32 elapsed = (ticks - start_ticks) * 10;
	
	vga_write("Done in ");
	vga_writeuint(elapsed,0);
	vga_writeln(" ms.");
	return 1;

}
