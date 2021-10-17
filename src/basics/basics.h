#ifndef MATRIX_BASICS_H
#define MATRIX_BASICS_H

/* basics.h: header to include very basic operations
 * on a matrix, such as transpose, inner-product,
 * cross-product, reshape, etc.
 * include <matrix/basics.h> to use that
 */

// note: next line is when we want to develop basics.h
//       the line after that is when we want to install and use basics.h
#include "../init/matrix.h"
// #include <matrix/matrix.h>

struct matrix *matrix_transpose(struct matrix *m);

struct matrix *matrix_reshape(struct matrix *m, size_t new_dim_count, size_t *new_dims);

struct matrix *matrix_innerproduct(struct matrix *m1, struct matrix *m2);

struct matrix *matrix_crossproduct(struct matrix *m1, struct matrix *m2);

double matrix_det(struct matrix *m);

// checking stuff

int matrix_issquare(struct matrix *m);

#endif // MATRIX_BASICS_H