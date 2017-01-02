%macro irqh 1
global irqh_%1
irqh_%1:
	push dword 0
	push dword %1
	jmp common_irqh
%endmacro

extern interrupt_handler

common_irqh:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, interrupt_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

; Hardware Interrupts
irqh 32 ;Programmable Interrupt Timer Interrupt
irqh 33 ;Keyboard Interrupt
irqh 34 ;Cascade (used internally by the two PICs. never raised)
irqh 35 ;COM2 (if enabled)
irqh 36 ;COM1 (if enabled)
irqh 37 ;LPT2 (if enabled)
irqh 38 ;Floppy Disk
irqh 39 ;LPT1 / Unreliable "spurious" interrupt (usually)
irqh 40 ;CMOS real-time clock (if enabled)
irqh 41 ;Free for peripherals / legacy SCSI / NIC
irqh 42 ;Free for peripherals / SCSI / NIC
irqh 43 ;Free for peripherals / SCSI / NIC
irqh 44 ;PS2 Mouse
irqh 45 ;FPU / Coprocessor / Inter-processor
irqh 46 ;Primary ATA Hard Disk
irqh 47 ;Secondary ATA Hard Disk
