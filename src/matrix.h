#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix {
    size_t dim_count; //<! number of dimensions
    size_t *dims; //<! number of elements at each dimension
    size_t dims_all; //<! multiplication of values in 'dims'
    double *values; //<! all elements in a vectorized array
    double *labels; //<! inserted tags for each dimension
};

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims);

int matrix_destroy(struct matrix *m);

char *matrix_strval_metadata(struct matrix *m);

void matrix_print_metadata_(struct matrix *m, char *name);

#define matrix_print_metadata(m) matrix_print_metadata_(m, #m)

#endif // MATRIX_H