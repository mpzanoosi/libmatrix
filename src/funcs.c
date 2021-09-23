#include "matrix.h"

struct matrix *matrix_func_exec(struct matrix *m, double (*f)(double))
{
    struct matrix *result = matrix_dup(m);
    int i;
    for (i = 0; i < result->e_count; i++) {
        result->e[i] = f(m->e[i]);
    }
    return result;
}

struct matrix *matrix_func_exec_label(struct matrix *m, double (*f)(double))
{
    struct matrix *result = matrix_dup(m);
    matrix_print_metadata(result);
    size_t i, offset;
    for (i = 0; i < result->e_count; i++) {
        result->e[i] = f(m->l[i]);
    }
    return result;
}