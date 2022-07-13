#include "matrix.h"

size_t matrix_array_mul(size_t count, size_t *a)
{
    size_t i;
    size_t result = 1;
    for (i = 0; i < count; i++) {
        result *= a[i];
    }
    return result;
}