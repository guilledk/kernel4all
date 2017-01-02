#include "memory.h"

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
