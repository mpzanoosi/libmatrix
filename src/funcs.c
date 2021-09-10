#include "matrix.h"

struct matrix *matrix_func_(struct matrix *m, double (*f)(double))
{
    struct matrix *result = matrix_dup(m);
    int i;
    for (i = 0; i < result->e_count; i++) {
        result->values[i] = f(m->values[i]);
    }
    return result;
}