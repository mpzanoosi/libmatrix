#include <stdio.h>
#include "matrix.h"

int main()
{
    size_t dim_count = 2;
    size_t dims[] = {2, 4};
    struct matrix *m1 = matrix_init_empty(dim_count, dims);
    matrix_print_metadata(m1);
    matrix_destroy(m1);
    return 0;
}