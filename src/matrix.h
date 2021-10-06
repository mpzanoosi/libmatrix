#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

// ***** numerical constants ***** //
#define MATRIX_PI   M_PI

struct matrix {
    size_t dim_count; //<! number of dimensions
    size_t *dims; //<! number of elements at each dimension
    size_t e_count; //<! total # elements = multiplication of values in 'dims'
    double *e; //<! all elements in a vectorized array
    size_t l_count; //<! total # labels = sum of values in 'dims'
    double *l; //<! inserted tags or labels for each dimension
};

typedef struct matrix *(*matrix_func)(struct matrix *);

// ***** core methods ***** //

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims);

struct matrix *matrix_init_empty_labels(size_t dim_count, struct matrix **labels);

struct matrix *matrix_init(size_t dim_count, size_t *dims);

struct matrix *matrix_init_labels(size_t dim_count, struct matrix **labels);

int matrix_destroy(struct matrix *m);

int matrix_destroy_batch(int count, ...);

struct matrix *matrix_dup(struct matrix *m);

int matrix_set_element(struct matrix *m, size_t *pos, double e);

size_t matrix_label_offset(struct matrix *m, size_t dim);

int matrix_set_labels(struct matrix *m, size_t dim, double *l);

int matrix_set_label_by_range(struct matrix *m, size_t dim, struct matrix *range);

struct matrix *matrix_range(double x1, double x2, double dx);

struct matrix *matrix_linspace(double x1, double x2, size_t count);

int matrix_calc_by_labels(matrix_func f, struct matrix *m);

int matrix_calc(matrix_func f, struct matrix *m);

// ***** matrix operators/operations ***** //

struct matrix *matrix_transpose(struct matrix *m);

struct matrix *matrix_reshape(struct matrix *m, size_t new_dim_count, size_t *new_dims);

struct matrix *matrix_innerproduct(struct matrix *m1, struct matrix *m2);

struct matrix *matrix_crossproduct(struct matrix *m1, struct matrix *m2);

// ***** mathematical functions ***** //

void matrix_func_exec_ewise_fast(struct matrix *m, double (*f)(double));

struct matrix *matrix_sin(struct matrix *m);

#define matrix_sin_linspace(x1, x2, count) ({\
    struct matrix *result = matrix_linspace(x1, x2, count); \
    matrix_func_exec_ewise_fast(result, sin); \
    result; })

struct matrix *matrix_cos(struct matrix *m);

#define matrix_cos_range(x1, x2, dx) ({\
    struct matrix *result = matrix_range(x1, x2, dx); \
    matrix_func_exec_ewise_fast(result, cos); \
    result; })

// ***** making strings and printing ***** //

char *matrix_strval(struct matrix *m);

char *matrix_strval_2d(struct matrix *m);

char *matrix_strval_metadata(struct matrix *m);

void matrix_print(struct matrix *m);

void matrix_print_metadata(struct matrix *m);

#define matrix_print_all(m) ({\
    printf("%s: \n", #m); \
    matrix_print_metadata(m); \
    matrix_print(m); })

// ***** end ***** //

#endif // MATRIX_H