#include "core/string.h"

u16 strlen(const char * str) {

	u16 size = 0;
	while(*str++) {
		size++;
	}
	return size;

}

void itoa(char * buf, u32 num, u8 base) {

	u32 tmp = num;
	int i = 0;
	int j;

	do {
		tmp = num % base;
		buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
	} while (num /= base);
	buf[i--] = '\0';

	for(j = 0; j < i; j++, i--) {
		tmp = buf[j];
		buf[j] = buf[i];
		buf[i] = tmp;
	}

}
