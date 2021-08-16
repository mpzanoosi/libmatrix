#ifndef MATH_MM_H
#define MATH_MM_H

#include <string.h>

#define structinit(type, name) \
        type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(*obj), obj##_copy); \
    (typeof(obj))memcpy(obj##_copy, obj, sizeof(typeof(*obj))); })

#define free_safe(x) ({free(x); x = NULL;})

#endif // MATH_MM_H