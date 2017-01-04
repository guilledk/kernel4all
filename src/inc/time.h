#ifndef _TIME_H_
#define _TIME_H_

#include "types.h"

/*
 * Right now the PIT is hardcoded to run at 100hz
 * Change pit_init() in pit.c to change hz
 */

u64 ticks;

void waitt(u32 t);
void waitms(u32 ms);

#endif
