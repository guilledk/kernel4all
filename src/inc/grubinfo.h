#ifndef _GRUBINFO_H_
#define _GRUBINFO_H_

#include "multiboot.h"
#include "vga.h"

void get_info(multiboot_info_t * mbd);
void get_infofull(multiboot_info_t * mbd);

#endif
