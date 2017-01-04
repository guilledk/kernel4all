#ifndef _ACPI_H_
#define _ACPI_H_

#include "types.h"
#include "memory.h"

struct rsd_ptr {

	u8 signature[8];
	u8 checksum;
	u8 oemID[6];
	u8 rev;
	u32 rsdt_address;

} __attribute__((packed));

struct rsd_ptr_v2 {
	
	struct rsd_ptr first_part;
	u32 len;
	u64 xsdt_addr;
	u8 xchecksum;
	u8 reserved[3];

} __attribute__((packed));

u8 acpi_check_rsdp(struct rsd_ptr * rsdp); //1 if valid 0 if not
void * acpi_get_rsdp(void);

#endif
