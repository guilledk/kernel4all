#include "pci.h"

const char * CLASS_CODES[20] = {

	"Device was built prior definition of the class code field",
	"Mass Storage Controller",
	"Network Controller",
	"Display Controller",
	"Multimedia Controller",
	"Memory Controller",
	"Bridge Device",
	"Simple Communication Controllers",
	"Base System Peripherals",
	"Input Devices",
	"Docking Stations",
	"Processors",
	"Serial Bus Controllers",
	"Wireless Controllers",
	"Intelligent I/O Controllers",
	"Satellite Communication Controllers",
	"Encryption/Decryption Controllers",
	"Data Acquisition and Signal Processing Controllers",
	"Reserved", //0x12 - 0xFE
	"Device does not fit any defined class." //0xFF

};

u32 pci_cfg_read_reg(u8 bus, u8 slot, u8 func, u8 offset) {

	u32 address;
	u32 lbus = (u32)bus;
	u32 lslot = (u32)slot;
	u32 lfunc = (u32)func;

	address = (u32)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((u32)0x80000000));

	outd(0xCF8, address);
	iowait();
	return ind(0xCFC);

}

void pci_get_info(struct pci_device * dev, u8 bus, u8 func, u8 slot) {
	
	u32 reg = 0;

	reg = pci_cfg_read_reg(bus,slot,func,0x00);
	dev->vendorID =  reg & 0x0000FFFF;
	dev->deviceID = (reg & 0xFFFF0000) >> 16;

	reg = pci_cfg_read_reg(bus,slot,func,0x04);
	dev->command = reg & 0x0000FFFF;
	dev->status = (reg & 0xFFFF0000) >> 16;

	reg = pci_cfg_read_reg(bus,slot,func,0x08);
	dev->revisionID = (reg & 0x000000FF);

	reg = pci_cfg_read_reg(bus,slot,func,0x10);
	dev->bar0 = reg;
	reg = pci_cfg_read_reg(bus,slot,func,0x14);
	dev->bar1 = reg;
	reg = pci_cfg_read_reg(bus,slot,func,0x18);
	dev->bar2 = reg;
	reg = pci_cfg_read_reg(bus,slot,func,0x1C);
	dev->bar3 = reg;
	reg = pci_cfg_read_reg(bus,slot,func,0x20);
	dev->bar4 = reg;
	reg = pci_cfg_read_reg(bus,slot,func,0x24);
	dev->bar5 = reg;

	reg = pci_cfg_read_reg(bus,slot,func,0x0C);
	dev->header_type =     (reg & 0x00FF0000) >> 16;


}

void pci_print(struct pci_device * dev) {

	vga_write("pci: ");
	vga_writehex(dev->vendorID,0);
	vga_write(":");
	vga_writehex(dev->deviceID,0);
	vga_newline();

}
