#ifndef MATH_ARRAY_H
#define MATH_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mm.h"

struct array {
    size_t count; //<! number of elements
    double *values; //<! stored values
};

struct array *array_init_empty(size_t count);

struct array *array_init_by_range(double start, double end, double dx);

int array_destroy(struct array *a);

void array_print_(struct array *a, char *name);

#define array_print(a) array_print_(a, #a)

void array_print_raw(struct array *a);

#endif // MATH_ARRAY_H