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
    size_t dim_count;   //<! number of dimensions
    size_t *dims;       //<! number of elements at each dimension
    size_t e_count;     //<! total # elements = multiplication of values in 'dims'
    double *e;          //<! all elements in a vectorized array
};

// init
struct matrix *matrix_init(size_t dim_count, size_t *dims);

int matrix_destroy(struct matrix *m);

int matrix_destroy_batch(int count, ...);

// iterators
#define matrix_for_each_element(i, m) \
    for (i = 0; i < (m)->e_count; i++)

#define matrix_for_x_in_col(i, m, c) \
    for (i = (c-1)*(m)->dims[0]; i < (c)*(m)->dims[0]; i++)

#define matrix_for_x_in_row(i, m, r) \
    for (i = (r-1); i <= (r-1) + ((m)->dims[1]-1)*(m)->dims[0]; i+=(m)->dims[0])


// basic - primary
matrix_transpose();
matrix_reshape();
matrix_isbigger();
matrix_issmaller();
matrix_isequal();
matrix_min_element();
matrix_max_element();
matrix_sort();
matrix_sort_rows();
matrix_sort_cols();
matrix_cat_row();		// concatenating by rows (vertically)
matrix_cat_col();		// concatenating by columns (horizontally)
matrix_split_row();		// splitting rows (vertically)
matrix_split_col();		// splitting rows (horizontally)

// basic - intermediate
matrix_add();
matrix_sub();
matrix_mul();
matrix_dotproduct();
matrix_crossproduct();
matrix_crossproduct();
matrix_det();
matrix_inv();
matrix_pinv();
matrix_piv(); // pivots
matrix_dec_eig();
matrix_dec_svd();
matrix_dec_qr();

// array
matrix_array_range();
matrix_array_linspace();
matrix_array_dotproduct();
matrix_array_crossproduct();
matrix_array_sum();
matrix_array_mul();

// check
matrix_issquare();
matrix_issymmetric();
matrix_ishermit();
matrix_iscov();

// memory management
matrix_save2file();

// ***** init ***** //

struct matrix *matrix_init(size_t dim_count, size_t *dims);

int matrix_destroy(struct matrix *m);

int matrix_destroy_batch(int count, ...);

int matrix_set_e(struct matrix *m, double *e);

int matrix_set_dims(struct matrix *m, double *dims);

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