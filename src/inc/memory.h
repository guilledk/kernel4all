#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "types.h"
#include "casm.h"

extern u32 kernel_end_addr;

struct page_directory {

	u32 entries[1024];

} __attribute__((packed));

struct page_table {

	u32 entries[1024];

} __attribute__((packed));

struct page_table * page_table_ptr;
struct page_directory * page_directory_ptr;

void paging_init(void);

void * memset(u8 * ptr, u8 val, u32 len);
void * memcpy(u8 * dst, u8 * src, u32 len);
u8 memcmp(u8 * a, u8 * b, u32 len);

#endif
