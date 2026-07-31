/*
 * This file is licensed under the terms described in the LICENSE
 * file located in the root directory of this source tree.
 */

 #ifndef MISC_H_
 #define MISC_H_
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
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

 #define REVERSE_ENDIANNESS_U16(x)   \
    (                                \
        ( (x >>  4) & 0x00FF ) |     \
        ( (x <<  4) & 0xFF00 )       \
    )

#define REVERSE_ENDIANNESS_U32(x)    \
    (                                \
        ( (x >> 24) & 0x000000FF ) | \
        ( (x >>  8) & 0x0000FF00 ) | \
        ( (x <<  8) & 0x00FF0000 ) | \
        ( (x << 24) & 0xFF000000 )   \
    )
 
#define BASE2_SCALE(value, src_width, dest_width) ((value) << ((dest_width) - (src_width)) | ((value) >> (src_width) - (((dest_width)) - ((src_width)))))

#ifdef __cplusplus
}
#endif

#endif // MISC_H_
