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

global inb

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
; 	 [esp ] The return address
inb:
	mov dx, [esp + 4]
	in al, dx
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
	
