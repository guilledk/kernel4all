#include "hardware/acpi.h"

u8 acpi_check_rsdp(struct rsd_ptr * rsdp) { //TODO: the if tree can be improved 

	const char * sig = "RSD PTR ";
	u8 sum = 0;

	if(memcmp((u8*)sig, (u8*)rsdp, 8)) {
	
		for(u16 i = 0; i < sizeof(struct rsd_ptr); i++) {
			sum += ((u8*)rsdp)[i];
		}

		if(sum == 0) {

			if(rsdp->rev > 0) {

				sum = 0;
				for(u16 i = 0; i < sizeof(struct rsd_ptr_v2); i++) {
					sum += ((u8*)rsdp)[i];
				}

				if(sum == 0) {
					return 1;
				}

			} else {
				return 1;
			}

		}

	}
		
	return 0;

}

void * acpi_get_rsdp(void) {

	u32 * addr;

	for(addr = (u32*)0x000E0000; (int)addr < 0x00100000; addr += 0x10 / sizeof(addr)) {

		if(acpi_check_rsdp((struct rsd_ptr *)addr))
			return (void *)addr;

	}

	u32 edba = *((u16*)0x40E);
	edba = edba * 0x10 & 0x000FFFFF;

	for(addr = (u32*)edba; (u32)addr < edba + 1024; addr += 0x10 / sizeof(addr)) {

		if(acpi_check_rsdp((struct rsd_ptr *)addr))
			return (void *)addr;

	}

	return 0;

}

u8 acpi_table_checksum(struct rsdt_header * table) {

	u8 sum = 0;

	for(u16 i = 0; i < table->len; i++) {
		
		sum += ((u8*)table)[i];

	}

	return sum == 0;

}

struct mcfg_table * acpi_get_mcfg_table(struct rsd_table * root) {

	u32 * ptr = (u32*) root;
	u32 entries = *(ptr + 1);
	entries = (entries - 36) / 4;
	ptr += 36 / 4;

	for(u32 i = 0; i < entries; i++) {
		
		struct rsdt_header * chead = (struct rsdt_header *)*ptr;

		if(memcmp(chead->signature,(u8*)"MCFG",4)) {
			if(acpi_table_checksum(chead)) {
				return (struct mcfg_table *)ptr;
			}
		}

		ptr++;

	}

	return 0;

}

void acpi_print_tables(struct rsd_table * root) {

	vga_writeln("ACPI SDTables:");

	char buf[8];
	
	u32 * ptr = (u32*) root;
	u32 entries = *(ptr + 1);
	entries = (entries - 36) / 4;
	ptr += 36 / 4;
	
	itoa(buf,entries,10);
	vga_write("RSDT entries: ");
	vga_writeln(buf);

	for(u32 i = 0; i < entries; i++) {
		
		struct rsdt_header * chead = (struct rsdt_header *)*ptr;
		memcpy((u8*)buf,chead->signature,4);
		buf[4] = 0;
		vga_write("\t+-");
		vga_write(buf);
		vga_write(": len: ");
		itoa(buf,chead->len,10);
		vga_writeln(buf);
		ptr++;

	}

}
