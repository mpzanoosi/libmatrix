#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdlib.h>
#include "set.h"

struct matrix {
    struct set *labels; //<! mapping of each elements of this matrix to a label (position)
    double *values; //<! values of the matrix; dimension information can be found in label
};

struct matrix *matrix_init_empty(size_t dim_count, size_t *counts);

struct matrix *matrix_init_labels(struct set *labels);

#define matrix_get_dim_count(this) (this)->labels->dim_count

#endif // MATRIX_MATRIX_H