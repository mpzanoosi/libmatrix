#ifndef MATRIX_MM_H
#define MATRIX_MM_H

#include <string.h>
#include <stdlib.h>

#define structinit(type, name) \
    type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(*obj), obj##_copy); \
    (typeof(obj))memcpy(obj##_copy, obj, sizeof(typeof(*obj))); })

#define free_safe(x) ({free(x); x = NULL;})

#define ptrccpy(dst, src, type, count) ({ \
    dst = (type *)calloc(count, sizeof(type)); \
    int i##_copy; \
    for (i##_copy = 0; i##_copy < count; i##_copy++) { \
        dst[i##_copy] = src[i##_copy]; \
    }})

#define memreset(ptr, count) memset(ptr, 0, count)

#endif // MATRIX_MM_H