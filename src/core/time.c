#include "core/time.h"

void waitt(u32 t) {

	u64 future = ticks + t;
	while(ticks < future) {}
	
}

void waitms(u32 ms) {

	waitt(ms / 10);

}
