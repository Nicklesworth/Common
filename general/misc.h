/*
 * This file is licensed under the terms described in the LICENSE
 * file located in the root directory of this source tree.
 */

#ifndef MISC_H_
#define MISC_H_
 
#include "local_types.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(a) ((a) > 0) ? (a) : (-(a))
#endif

#define MEMBER_OFFSET(type, member) (uint32_t) &(((type *) 0)->member)

#define REVERSE_ENDIANNESS_U16(x)	\
(                                	\
	( (x >>  4) & 0x00FF ) |     	\
	( (x <<  4) & 0xFF00 )       	\
)

#define REVERSE_ENDIANNESS_U32(x)	\
(                                	\
	( (x >> 24) & 0x000000FF ) | 	\
	( (x >>  8) & 0x0000FF00 ) | 	\
	( (x <<  8) & 0x00FF0000 ) | 	\
	( (x << 24) & 0xFF000000 )   	\
)
 
#define BASE2_SCALE(value, src_width, dest_width) ((value) << ((dest_width) - (src_width)) | ((value) >> (src_width) - (((dest_width)) - ((src_width)))))

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

#define BIT_SET(var, bit) ((var) |= (1 << (bit)))
#define BIT_CLR(var, bit) ((var) &= ~(1 << (bit)))
#define BIT_TGL(var, bit) ((var) ^= (1 << (bit)))
#define BIT_TST(var, bit) ((var) & (1 << (bit)))

#ifndef bitfield_array_t
#define bitfield_array_t uint8_t
#endif

#define BITFIELD_PACKING (8*sizeof(bitfield_array_t))
#define BYTES_REQUIRED_FOR_BITFIELD_ARRAY(num_bits) (((num_bits)+BITFIELD_PACKING-1)/BITFIELD_PACKING)
#define	BITFIELD_ARRAY(var_name, num_bits) bitfield_array_t var_name[BYTES_REQUIRED_FOR_BITFIELD_ARRAY(num_bits)]

#define	GET_BITFIELD_ARRAY_BIT(var_name, bit)	( var_name[(bit)/BITFIELD_PACKING] & 	(1 << ( (bit) % BITFIELD_PACKING) ) )
#define	SET_BITFIELD_ARRAY_BIT(var_name, bit)	( var_name[(bit)/BITFIELD_PACKING] |= 	(1 << ( (bit) % BITFIELD_PACKING) ) )
#define	CLR_BITFIELD_ARRAY_BIT(var_name, bit)	( var_name[(bit)/BITFIELD_PACKING] &= ~	(1 << ( (bit) % BITFIELD_PACKING) ) )
#define TGL_BITFIELD_ARRAY_BIT(var_name, bit)	( var_name[(bit)/BITFIELD_PACKING] ^= 	(1 << ( (bit) % BITFIELD_PACKING) ) )

static inline void ChangeBitfieldArrayBit(bitfield_array_t* b, uint32_t bit, bool state)
{
	if(state)
		SET_BITFIELD_ARRAY_BIT(b, bit);
	else
		CLR_BITFIELD_ARRAY_BIT(b, bit);
}

#endif // MISC_H_
