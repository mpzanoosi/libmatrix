#ifndef MATRIX_ARRAY_H
#define MATRIX_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mm.h"

char *array_strval(double *a, size_t count);

char *array_strval_size_t(size_t *a, size_t count);

char *array_strval_vidxs(double *a, size_t *vidxs, size_t count);

#endif // MATRIX_ARRAY_H