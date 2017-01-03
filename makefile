NAME = kernel4all
VERSION = 1
OUT = k4a.elf
INC = src/inc/
GCC = i686-elf-gcc
ASM = nasm
LDF = link.ld
CSRC = $(wildcard src/*.c)
ASRC = $(wildcard src/*.asm)
COBJ = $(CSRC:src/%.c=out/%.o)
AOBJ = $(ASRC:src/%.asm=out/%.o)
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	 -nostartfiles -nodefaultlibs -Wall -Wextra -I $(INC)
LFLAGS = -melf_i386
AFLAGS = -f elf32

default: run
	

build:
	$(foreach SRC, $(CSRC), $(GCC) $(CFLAGS) -c $(SRC) -o $(SRC:src/%.c=out/%.o);)
	$(foreach SRC, $(ASRC), $(ASM) $(AFLAGS) $(SRC) -o $(SRC:src/%.asm=out/%.o);)

.PHONY: clean link run default geniso

clean:
	rm -f out/*.o $(OUT)
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

run: geniso
	qemu-system-i386 -cdrom "$(NAME)-v$(VERSION).iso"
