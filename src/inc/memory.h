#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "types.h"

void * memset(u8 * ptr, u8 val, u32 len);
void * memcpy(u8 * dst, u8 * src, u32 len);
u8 memcmp(u8 * a, u8 * b, u32 len);

#endif
