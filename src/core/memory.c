#include "core/memory.h"

void paging_init(void) {

	page_directory_ptr = (struct page_directory *)0x9C000;
	page_table_ptr = (struct page_table *)0x9D000;

	//Fill page table
	u32 caddr = 0;
	for(u16 i = 0; i < 1024; i++) {

		page_table_ptr->entries[i] = caddr | 3; //sudo, rw, present (0b011)
		caddr += 4096;

	}

	//Fill page directory
	page_directory_ptr->entries[0] = (u32)page_table_ptr; 
	page_directory_ptr->entries[0] = page_directory_ptr->entries[0] | 3; 
					 // sudo, rw, present (0b011)

	for(u16 i = 1; i < 1024; i++) {
		
		page_directory_ptr->entries[i] = 0 | 2; //sudo, rw, not present (0b010)

	}

	//Enable paging
	write_cr3((u32)page_directory_ptr);
	write_cr0(read_cr0() | 0x80000000);
}

void * memset(u8 * ptr, u8 val, u32 len) {

	u8 * start = ptr;
	while(len--) {
		
		*ptr++ = val;
	
	}
	return start;

}

void * memcpy(u8 * dst, u8 * src, u32 len) {

	u8 * start = dst;
	while(len--) {
	
		*dst++ = *src++;

	}
	return start;

}

u8 memcmp(u8 * a, u8 * b, u32 len) {

	u8 ret = 1;
	for(u32 i = 0; i < len; i++) {
		if(*(a+i) != *(b+i)) {
			ret = 0;
			break;
		}
	}
	return ret;

}
