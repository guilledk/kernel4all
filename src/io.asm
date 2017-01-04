global outb

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp ] return address
outb:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

global outw

; outw - send a word to an I/O port
; stack: [esp + 8] the data word
;        [esp + 4] the I/O port
;        [esp ] return address
outw:
	mov ax, [esp + 8]
	mov dx, [esp + 4]
	out dx, ax
	ret

global outd

; outw - send a double word to an I/O port
; stack: [esp + 8] the data double word
;        [esp + 4] the I/O port
;        [esp ] return address
outd:
	mov eax, [esp + 8]
	mov dx, [esp + 4]
	out dx, eax
	ret

global inb

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
; 	 [esp ] The return address
inb:
	mov dx, [esp + 4]
	in al, dx
	ret

global inw

; inb - returns a word from the given I/O port
; stack: [esp + 4] The address of the I/O port
; 	 [esp ] The return address
inw:
	mov dx, [esp + 4]
	in ax, dx
	ret

global ind

; inb - returns a double word from the given I/O port
; stack: [esp + 4] The address of the I/O port
; 	 [esp ] The return address
ind:
	mov dx, [esp + 4]
	in eax, dx
	ret

global iowait

; iowait - Forces the CPU to wait for an I/O operation to complete. 
; only use this when there's nothing like a status register or an IRQ
; to tell you the info has been received.
iowait:
	jmp one
one:
	jmp two
two:
	ret

global read_cr0

read_cr0:
	mov eax, cr0
	retn

global write_cr0

write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	retn

global read_cr3

read_cr3:
	mov eax, cr3
	retn

global write_cr3

write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
