#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

typedef signed char		i8;
typedef signed short		i16;
typedef signed int		i32;
typedef signed long long	i64;

static inline u8 bit(u32 num, u8 k) {

	return (num >> k) & 1;

}

#endif
