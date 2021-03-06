#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

// ***** numerical constants ***** //
#define MATRIX_PI   M_PI

// ***** basic structure ***** //
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

// todo: develop this function
int matrix_calc_by_labels(matrix_func f, struct matrix *m);

// todo: develop this function
int matrix_calc(matrix_func f, struct matrix *m);

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