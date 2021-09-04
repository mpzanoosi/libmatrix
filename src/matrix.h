#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct matrix {
    size_t dim_count; //<! number of dimensions
    size_t *dims; //<! number of elements at each dimension
    size_t e_count; //<! total # elements = multiplication of values in 'dims'
    double *values; //<! all elements in a vectorized array
    double **labels; //<! inserted tags for each dimension
};

// ***** core methods ***** //

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims);

struct matrix *matrix_init_empty_labels(size_t dim_count, struct matrix **ranges);

int matrix_destroy(struct matrix *m);

int matrix_set_value(struct matrix *m, size_t *pos, double value);

int matrix_set_label_by_range(struct matrix *m, size_t dim, struct matrix *range);

struct matrix *matrix_range(double x1, double x2, double dx);

struct matrix *matrix_linspace(double x1, double x2, size_t count);

// ***** making strings and printing ***** //

char *matrix_strval(struct matrix *m);

char *matrix_strval_2d(struct matrix *m);

char *matrix_strval_metadata(struct matrix *m);

void matrix_print(struct matrix *m);

void matrix_print_metadata(struct matrix *m);

#endif // MATRIX_H