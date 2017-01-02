global gdt_init

gdt_init:
	lgdt [gdt_info]
	jmp 0x08:flush_regs

gdt_start:
	dq 0x0000000000000000 ;NULL descriptor
	dq 0x00CF9A000000FFFF ;PL0 Kernel code
	dq 0x00CF92000000FFFF ;PL0 Kernel data

gdt_info:
	dw gdt_info - gdt_start - 1
	dq gdt_start

flush_regs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
