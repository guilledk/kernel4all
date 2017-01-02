global loader

MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

KERNEL_STACK_SIZE equ 4096 ;4kb stack

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
align 4

extern kernel_main

loader:
	mov esp, kernel_stack + KERNEL_STACK_SIZE ;init stack
	mov eax, 0xCAFEBABE

	call kernel_main
