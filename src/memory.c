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
