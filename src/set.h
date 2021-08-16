#ifndef MATH_SET_H
#define MATH_SET_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mm.h"
#include "array.h"

struct set {
    size_t dim_count; //<! number of dimensions
    size_t *counts; //<! number of elements at each dimension
    size_t counts_all; //<! multiplying all values of counts
    struct array **values; //<! per-dimension arrays (one pointer for each dimension)
};

struct set *set_init_empty(size_t dim_count, size_t *counts);

struct set *set_init_by_array_2d(struct array *a1, struct array *a2);

int set_destroy(struct set *s);

void set_print_(struct set *s, char *name);

#define set_print(s) set_print_(s, #s)

#endif // MATH_SET_H