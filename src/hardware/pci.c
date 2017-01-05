#include "hardware/pci.h"

u8  pci_inb(u32 id, u16 reg) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	iowait();
	return inb(PCI_CONFIG_DATA + (reg & 0x03));

}

u16 pci_inw(u32 id, u16 reg) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	iowait();
	return inw(PCI_CONFIG_DATA + (reg & 0x02));

}

u32 pci_ind(u32 id, u16 reg) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	iowait();
	return ind(PCI_CONFIG_ADDR);

}

void pci_outb(u32 id, u16 reg, u8 data) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	outb(PCI_CONFIG_DATA + (reg & 0x03), data);

}

void pci_outw(u32 id, u16 reg, u16 data) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	outw(PCI_CONFIG_DATA + (reg & 0x02), data);

}

void pci_outd(u32 id, u16 reg, u32 data) {

	u32 addr = 0x80000000 | id | (reg & 0xFC);
	outd(PCI_CONFIG_ADDR, addr);
	outd(PCI_CONFIG_DATA, data);

}

void pci_get_info(struct pci_device_info * pdev, u8 bus, u8 dev, u8 func) {
	
	u32 id = PCI_MAKE_ID(bus,dev,func);
	
	pdev->vendorID = pci_inw(id, PCI_CONFIG_VENDOR_ID);

	if(pdev->vendorID == 0xFFFF) {
		return;
	}

	pdev->deviceID = pci_inw(id, PCI_CONFIG_DEVICE_ID);
	pdev->status = pci_inw(id, PCI_CONFIG_STATUS);
	pdev->command = pci_inw(id, PCI_CONFIG_COMMAND);
	
	pdev->class_code = pci_inb(id, PCI_CONFIG_CLASS_CODE);
	pdev->subclass = pci_inb(id, PCI_CONFIG_SUBCLASS);
	pdev->prog_if = pci_inb(id, PCI_CONFIG_PROG_INTF);

	pdev->revisionID = pci_inb(id, PCI_CONFIG_REVISION_ID);
	pdev->header_type = pci_inb(id, PCI_CONFIG_HEADER_TYPE);

}

void pci_print(struct pci_device_info * pdev, u8 bus, u8 dev, u8 func) {

	vga_write("(");
	vga_writeuint(bus,3);
	vga_write(":");
	vga_writeuint(dev,2);
	vga_write(".");
	vga_writeuint(func,0);
	vga_write(") ");
	vga_writehex(pdev->vendorID,0);
	vga_write(":");
	vga_writehex(pdev->deviceID,0);
	vga_write(": ");
	vga_write(pci_class_name(pdev->class_code,pdev->subclass,pdev->prog_if));
	vga_newline();

}
