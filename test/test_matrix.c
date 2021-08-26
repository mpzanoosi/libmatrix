#include <stdio.h>
#include "matrix.h"

int matrix_1D_test()
{
    // M[i] = i^2
    size_t dim_count = 1;
    size_t dims[] = {6};
    struct matrix *m1 = matrix_init_empty(dim_count, dims);
    size_t pos[1];
    int i;
    for (i = 1; i <= 6; i++) {
        pos[0] = i;
        matrix_set_value(m1, pos, i*i);
    }
    matrix_print_metadata(m1);
    matrix_print(m1);
    matrix_destroy(m1);
    return 0;
}

int matrix_2D_test()
{
    // M[i,j] = 2*i + j^2
    size_t dim_count = 2;
    size_t dims[] = {6,3};
    struct matrix *m1 = matrix_init_empty(dim_count, dims);
    size_t pos[2];
    int i, j;
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 3; j++) {
            pos[0] = i;
            pos[1] = j;
            matrix_set_value(m1, pos, 2*i + j*j);
        }
    }
    matrix_print_metadata(m1);
    matrix_print(m1);
    matrix_destroy(m1);
    return 0;
}

int main()
{
    matrix_2D_test();
    return 0;
}