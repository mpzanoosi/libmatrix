#include <stdio.h>
#include "matrix.h"

int main()
{
    size_t dim_count = 3;
    size_t dims[] = {3, 4, 5};
    size_t pos[] = {2, 2, 2};
    struct matrix *m = matrix_init_empty(dim_count, dims);
    // matrix_print(m);
    // printf("--- %zu\n", sizeof(double));
    matrix_destroy(m);
    return 0;
}