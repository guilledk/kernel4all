#include "interrupts/interrupt.h"
#include "hardware/grubinfo.h"
#include "hardware/acpi.h"
#include "shell/shell.h"

//Halt And Catch Fire
void hcf(void) { for(;;); }

void kernel_main(multiboot_info_t * mbd) {

	vga_init();
	vga_clear();
	vga_write("kernel for all v1\n");

	gdt_init();

	idt_init();

	get_info(mbd);

	struct rsd_ptr * rsdp = acpi_get_rsdp();
	if(rsdp != 0){
		vga_writeln("Root System Description Pointer Found!");
		char rev[8];
		itoa(rev,rsdp->rev,10);
		vga_write("\trev: ");
		vga_writeln(rev);
		if(rsdp->rev > 0) {
			itoa(rev,((struct rsd_ptr_v2 *)rsdp)->len,10);
			vga_write("\tRSDT len: ");
			vga_writeln(rev);
		}
		
	}

	acpi_print_tables((struct rsd_table *)rsdp->rsdt_address);
	
	vga_newline();

	kb_init();

	paging_init();

	vga_write("kernel size in memory: ");
	vga_writeuint((u32)&kernel_end_addr - 0xF4240);
	vga_write(" bytes.\n");

	shell_init();

	hcf();

}
