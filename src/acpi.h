#ifndef _ACPI_H_
#define _ACPI_H_

#include "types.h"
#include "memory.h"
#include "vga.h"

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

struct rsdt_header {
	
	u8 signature[4];
	u32 len;
	u8 rev;
	u8 checksum;
	u8 oemID[6];
	u8 oemtID[8];
	u32 oem_rev;
	u32 creatorID;
	u32 creator_rev;

} __attribute__((packed));

struct rsd_table {

	struct rsdt_header head;
	u32 * other_sdt_ptr;

} __attribute__((packed));

struct mcfg_csbaa { //Configuration space base address allocation

	u64 base_addr;
	u16 pci_seg_group_num;
	u8 start_pci_bus_num;
	u8 end_pci_bus_num;
	u8 reserved[4];

} __attribute__((packed));

struct mcfg_table {

	struct rsdt_header head;
	u8 reserved[8];
	struct mcfg_csbaa * csbaas;

} __attribute__((packed));

u8 acpi_check_rsdp(struct rsd_ptr * rsdp); //1 if valid 0 if not
void * acpi_get_rsdp(void);

u8 acpi_table_checksum(struct rsdt_header * table);
struct mcfg_table * acpi_get_mcfg_table(struct rsd_table * root);
void acpi_print_tables(struct rsd_table * root);


#endif
