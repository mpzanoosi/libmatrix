#ifndef MATRIX_FUNCS_H
#define MATRIX_FUNCS_H

/* funcs.h: header to include very basic operations
 * on a matrix, such as transpose, inner-product,
 * cross-product, reshape, etc.
 * include <matrix/funcs.h> to use that
 */

// note: next line is when we want to develop funcs.h
//       the line after that is when we want to install and use funcs.h
#include "../init/matrix.h"
// #include <matrix/matrix.h>
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

#endif // MATRIX_FUNCS_H