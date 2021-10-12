#include "funcs.h"
#include "../init/init.h"

struct matrix *matrix_func_exec_ewise(struct matrix *m, double (*f)(double))
{
    struct matrix *result = matrix_dup(m);
    int i;
    for (i = 0; i < result->e_count; i++) {
        result->e[i] = f(m->e[i]);
    }
    return result;
}

void matrix_func_exec_ewise_fast(struct matrix *m, double (*f)(double))
{
    int i;
    for (i = 0; i < m->e_count; i++) {
        m->e[i] = f(m->e[i]);
    }
}

struct matrix *matrix_func_exec(size_t dim_count, ...)
{
    // struct matrix **labels = (struct matrix *)calloc(dim_count, sizeof(struct matrix *));
    // matrix_func *funcs = (matrix_func *)calloc(dim_count, sizeof(matrix_func));

    // // extracting labels and corresponding functions
    // int i;
    // va_list ap;
    // va_start(ap, dim_count);
    // for (i = 0; i < dim_count; i++) {
    //     labels[i] = va_arg(ap, struct matrix *);
    //     funcs[i] = va_arg(ap, matrix_func);
    // }
    // va_end(ap);

    // // making result matrix based on aquired labels
    // struct matrix *result = matrix_init_labels(dim_count, labels);

    // // applying functions 

    // return result;
    return NULL;
}

struct matrix *matrix_sin(struct matrix *m)
{
    return matrix_func_exec_ewise(m, sin);
}

struct matrix *matrix_cos(struct matrix *m)
{
    return matrix_func_exec_ewise(m, cos);
}