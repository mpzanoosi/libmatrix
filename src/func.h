#ifndef MATRIX_FUNC_H
#define MATRIX_FUNC_H

#include "matrix.h"
#include "set.h"

typedef double (*func)(int dim, double *x);

int func_exec(struct matrix *y, func f, struct set *s);

#endif // MATRIX_FUNC_H