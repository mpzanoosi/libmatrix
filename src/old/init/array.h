#ifndef MATRIX_ARRAY_H
#define MATRIX_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ***** array calculations ***** //

size_t matrix_array_pimult(size_t count, size_t *intvals);

size_t matrix_array_sigmasum(size_t count, size_t *intvals);

// ***** array stringifying ***** //

#define MATRIX_DOUBLE_PREC  2 // default precision for printing

char *matrix_array_strval_double(double *a, size_t count);

char *matrix_array_strval_double_vidxs(double *a, size_t *vidxs, size_t count);

char *matrix_array_strval_size_t(size_t *a, size_t count);


#endif // MATRIX_ARRAY_H