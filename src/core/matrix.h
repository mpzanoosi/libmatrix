#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

// basic structure
struct matrix {
	size_t dim_count;   //<! number of dimensions
	size_t *dims;       //<! number of elements at each dimension
	size_t e_count;     //<! total # elements = multiplication of values in 'dims'
	double *e;          //<! all elements in a vectorized array
};

// numerical definitions
#define MATRIX_PI   M_PI

// functional definitions
#define structalloc(type, name) \
	type *name = (type *)malloc(sizeof(type))
#define structdup(obj) ({ \
	structalloc(typeof(*obj), obj##_copy); \
	(typeof(obj))memcpy(obj##_copy, obj, sizeof(typeof(*obj))); })
#define ptrccpy(dst, src, type, count) ({ \
	dst = (type *)calloc(count, sizeof(type)); \
	int i; \
	for (i = 0; i < count; i++) { \
		dst[i] = src[i]; \
	}})
#define free_safe(x) ({free(x); x = NULL;})

// enums
typedef enum {
	MATRIX_SORT_ASCEND,
	MATRIX_SORT_DESCEND
} matrix_sort_type;

// custom function type
typedef struct matrix *(*matrix_func)(struct matrix *);

// init
struct matrix *matrix_init(size_t dim_count, size_t *dims); // initializing a matrix
int matrix_destroy(struct matrix *A); // freeing up a matrix
int matrix_destroy_batch(int count, ...); // freeing up a bunch of matrices

// iterators
#define matrix_for_each_element(i, A) \
	for (i = 0; i < (A)->e_count; i++)
#define matrix_iter_col(i, A, c) \
	for (i = (c-1)*(A)->dims[0]; i < (c)*(A)->dims[0]; i++)
#define matrix_iter_row(i, A, r) \
	for (i = (r-1); i <= (r-1) + ((A)->dims[1]-1)*(A)->dims[0]; i+=(A)->dims[0])


// basic - primary
struct matrix *matrix_transpose(struct matrix *A);
struct matrix *matrix_reshape(struct matrix *A, size_t new_dim_count, size_t *new_dims);
int matrix_isbigger(struct matrix *A, double x);
int matrix_issmaller(struct matrix *A, double x);
int matrix_isequal(struct matrix *A, struct matrix *B);
double matrix_min_element(struct matrix *A);
double matrix_max_element(struct matrix *A);
struct matrix *matrix_sort_rows(struct matrix *A, matrix_sort_type sort_type, size_t flag_row);
struct matrix *matrix_sort_cols(struct matrix *A, matrix_sort_type sort_type, size_t flag_col);
struct matrix *matrix_cat_row(struct matrix *A, struct matrix *B);		// concatenating by rows (vertically)
struct matrix *matrix_cat_col(struct matrix *A, struct matrix *B);		// concatenating by columns (horizontally)
int matrix_split_row(struct matrix *A, struct matrix *A_left, struct matrix *A_right);		// splitting rows (vertically)
int matrix_split_col(struct matrix *A, struct matrix *A_up, struct matrix *A_down);		// splitting rows (horizontally)

// basic - intermediate
struct matrix *matrix_add(struct matrix *A, struct matrix *B);
struct matrix *matrix_sub(struct matrix *A, struct matrix *B);
struct matrix *matrix_mul(struct matrix *A, struct matrix *B);
int matrix_calc(struct matrix *A, matrix_func f); // sin, cos, tan, ...; useful with <math.h> library
struct matrix *matrix_dotproduct(struct matrix *A, struct matrix *B);
struct matrix *matrix_crossproduct(struct matrix *A, struct matrix *B);
double matrix_det(struct matrix *A);
struct matrix *matrix_inv(struct matrix *A);
struct matrix *matrix_pinv(struct matrix *A);
int matrix_piv(struct matrix *A, double *p, size_t p_count); // pivots
int matrix_dec_eigvalue(struct matrix *A, struct matrix *lambda);
int matrix_dec_eig(struct matrix *A, struct matrix *lamda, struct matrix *v);
int matrix_dec_svd(struct matrix *A, struct matrix *U, struct matrix *S, struct matrix *V);
int matrix_dec_qr(struct matrix *A, struct matrix *Q, struct matrix *R);

// array
struct matrix *matrix_array_range(double x1, double x2, double dx);
struct matrix *matrix_array_linspace(double x1, double x2, size_t count);
struct matrix *matrix_array_dotproduct(struct matrix *a, struct matrix *b);
struct matrix *matrix_array_crossproduct(struct matrix *a, struct matrix *b);
double matrix_array_sum(size_t count, double *a);
size_t matrix_array_mul(size_t count, size_t *a);
struct matrix *matrix_array_conv(struct matrix *a, struct matrix *b);

// check
int matrix_isarray(struct matrix *A);
int matrix_issquare(struct matrix *A);
int matrix_issymmetric(struct matrix *A);
int matrix_ishermit(struct matrix *A);
int matrix_iscov(struct matrix *A);

// memory management
struct matrix *matrix_dup(struct matrix *A); // duplicating a matrix (including contents)
struct matrix *matrix_save2file(struct matrix *A, char *filename);

// making strings and printing
char *matrix_strval_2d(struct matrix *m);
char *matrix_strval_metadata(struct matrix *m);
void matrix_print(struct matrix *m);
void matrix_print_metadata(struct matrix *m);
#define matrix_print_all(m) ({\
	printf("%s: \n", #m); \
	matrix_print_metadata(m); \
	matrix_print(m); })

#endif // MATRIX_H