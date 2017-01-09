NAME = kernel4all
VERSION = 1
OUT = k4a.elf
INC = src/include/
GCC = i686-elf-gcc
ASM = nasm
LDF = link.ld
CSRC = $(shell find src/ -type f -name '*.c')
ASRC = $(shell find src/ -type f -name '*.asm')
COBJ = $(patsubst src/%.c, out/%.o, $(CSRC))
AOBJ = $(patsubst src/%.asm, out/%.o, $(ASRC))
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	 -nostartfiles -nodefaultlibs -Wall -Wextra -I $(INC)
LFLAGS = -melf_i386
AFLAGS = -f elf32

default: run

build:
	mkdir -p out/core
	mkdir -p out/hardware/usb
	mkdir -p out/interrupts
	mkdir -p out/shell/programs
	$(foreach SRC, $(CSRC), $(GCC) $(CFLAGS) -c $(SRC) -o $(SRC:src/%.c=out/%.o);)
	$(foreach SRC, $(ASRC), $(ASM) $(AFLAGS) $(SRC) -o $(SRC:src/%.asm=out/%.o);)

.PHONY: clean link run default geniso genusb

clean:
	rm -rdf out/* $(OUT)
	rm -rdf iso

link: build
	ld $(LFLAGS) -T $(LDF) $(COBJ) $(AOBJ) -o $(OUT)

geniso: link
	mkdir -p iso/boot/grub
	cp grub/stage2_eltorito iso/boot/grub
	cp $(OUT) iso/boot
	cp grub/menu.lst iso/boot/grub
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A "$(NAME) v$(VERSION)" \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o "$(NAME)-v$(VERSION).iso" \
		iso

genusb: geniso
	cp grub/grub.cfg iso/boot/grub
	grub-mkrescue -o "$(NAME)-v$(VERSION).iso" iso
	

run: genusb
	qemu-system-i386 --cdrom "$(NAME)-v$(VERSION).iso"
