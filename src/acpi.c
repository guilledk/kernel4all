#include "acpi.h"

u8 acpi_check_rsdp(struct rsd_ptr * rsdp) {

	const char * sig = "RSD PTR ";
	u8 * bptr;
	u8 check = 0;

	if(memcmp((u8*)sig, (u8*)rsdp, 8)) {
	
		bptr = (u8*)rsdp;
		for(u8 i = 0; i < sizeof(struct rsd_ptr); i++) {
			check += *bptr;
			bptr++;
		}

		if(check == 0) {

			if(rsdp->rev > 0) {

				check = 0;
				bptr = (u8*)rsdp;
				for(u8 i = 0; i < sizeof(struct rsd_ptr_v2); i++) {
					check += *bptr;
					bptr++;
				}

				if(check == 0) {
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
