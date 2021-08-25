#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix {
    size_t dim_count; //<! number of dimensions
    size_t *dims; //<! number of elements at each dimension
    size_t e_count; //<! total # elements = multiplication of values in 'dims'
    double *values; //<! all elements in a vectorized array
    double *labels; //<! inserted tags for each dimension
};

// ***** core methods ***** //

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims);

int matrix_destroy(struct matrix *m);

size_t matrix_get_vidx(struct matrix *m, size_t *pos); // index of vectorized matrix m

void matrix_get_vidxs_row(struct matrix *m, size_t *idxs, size_t row); // vectorized indexes of a row

int matrix_set_value(struct matrix *m, size_t *pos, double value);

// ***** printing and stringifying ***** //

char *matrix_strval_metadata(struct matrix *m);

void matrix_print_metadata_(struct matrix *m, char *name);

#define matrix_print_metadata(m) matrix_print_metadata_(m, #m)

char *matrix_strval(struct matrix *m);

void matrix_print_(struct matrix *m, char *name);

#define matrix_print(m) matrix_print_(m, #m)

#endif // MATRIX_H