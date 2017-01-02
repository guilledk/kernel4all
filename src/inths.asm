global load_idt
extern idtr
load_idt:
	lidt [idtr]
	sti
	ret

%macro no_err_inth 1
global inth_%1
inth_%1:
	push dword 0
	push dword %1
	jmp common_inth
%endmacro

%macro err_inth 1
global inth_%1
inth_%1:
	push dword %1
	jmp common_inth
%endmacro

extern exception_handler

common_inth:
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
	mov eax, exception_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

no_err_inth  0 ;Division By Zero Exception
no_err_inth  1 ;Debug Exception
no_err_inth  2 ;Non Maskable Interrupt Exception
no_err_inth  3 ;Breakpoint Exception
no_err_inth  4 ;Into Detected Overflow Exception
no_err_inth  5 ;Out of Bounds Exception
no_err_inth  6 ;Invalid Opcode Exception
no_err_inth  7 ;No Coprocessor Exception
   err_inth  8 ;Double Fault Exception
no_err_inth  9 ;Coprocessor Segment Overrun Exception
   err_inth 10 ;Bad TSS Exception
   err_inth 11 ;Segment Not Present Exception
   err_inth 12 ;Stack Fault Exception
   err_inth 13 ;General Protection Fault Exception
   err_inth 14 ;Page Fault Exception
no_err_inth 15 ;Unknown Interrupt Exception
no_err_inth 16 ;Coprocessor Fault Exception
no_err_inth 17 ;Alignment Check Exception (486+)
no_err_inth 18 ;Machine Check Exception (Pentium/586+)

no_err_inth 19 ;Reserved Exception
no_err_inth 20 ;Reserved Exception
no_err_inth 21 ;Reserved Exception
no_err_inth 22 ;Reserved Exception
no_err_inth 23 ;Reserved Exception
no_err_inth 24 ;Reserved Exception
no_err_inth 25 ;Reserved Exception
no_err_inth 26 ;Reserved Exception
no_err_inth 27 ;Reserved Exception
no_err_inth 28 ;Reserved Exception
no_err_inth 29 ;Reserved Exception
no_err_inth 30 ;Reserved Exception
no_err_inth 31 ;Reserved Exception
