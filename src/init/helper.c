#include "helper.h"

size_t matrix_pimult(size_t count, size_t *intvals)
{
    if (count < 0)
        return -1;
        
    if (count == 0)
        return 1;

    size_t i, result = 1;
    for (i = 0; i < count; i++) {
        result *= intvals[i];
    }
    return result;
}

size_t matrix_sigmasum(size_t count, size_t *intvals)
{
    if (count < 0)
        return -1;

    if (count == 0)
        return 0;

    size_t i, result = 0;
    for (i = 0; i < count; i++) {
        result += intvals[i];
    }
    return result;
}