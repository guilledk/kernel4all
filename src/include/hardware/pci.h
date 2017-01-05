#ifndef _PCI_H_
#define _PCI_H_

#include "core/casm.h"
#include "core/string.h"
#include "core/vga.h"

extern const char * CLASS_CODES[20];

struct pci_device {

	u16 vendorID;
	u16 deviceID;
	u16 status;
	u16 command;

	u32 bar0;
	u32 bar1;
	u32 bar2;
	u32 bar3;
	u32 bar4;
	u32 bar5;
	
	u8 class_code;
	u8 revisionID;
	u8 header_type;

};

u32 pci_cfg_read_reg(u8 bus, u8 slot, u8 func, u8 offset);
void pci_get_info(struct pci_device * dev, u8 bus, u8 func, u8 slot);
void pci_print(struct pci_device * dev);

#endif
