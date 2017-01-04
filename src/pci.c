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

	reg = pci_cfg_read_reg(bus,slot,func,0x0C);
	dev->header_type =     (reg & 0x00FF0000) >> 16;


}

void pci_print(struct pci_device * dev) {

	char buf[8];
	itoa(buf,dev->vendorID,10);
	vga_write("pci device:\n\tvendor: ");
	vga_writeln(buf);
	itoa(buf,dev->deviceID,10);
	vga_write("\tdevice: ");
	vga_writeln(buf);
	itoa(buf,dev->bar0,10);
	vga_write("\tBAR0: ");
	vga_writeln(buf);
	itoa(buf,dev->revisionID,10);
	vga_write("\trev ");
	vga_writeln(buf);
	itoa(buf,dev->header_type,10);
	vga_write("\thtype ");
	vga_writeln(buf);
	vga_write("\tclass: ");
	if(dev->class_code < 0x12) {
		vga_writeln(CLASS_CODES[dev->class_code]);
	} else {
		if(dev->class_code == 0xFF) {
			vga_writeln(CLASS_CODES[19]);
		} else {
			vga_writeln(CLASS_CODES[18]);
		}
	}
	

}
