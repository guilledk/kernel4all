#include "time.h"

void waitt(u32 t) {

	u64 future = ticks + t;
	while(ticks < future) {}
	
}
