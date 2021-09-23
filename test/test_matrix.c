#include "matrix.h"

int matrix_1D_test1()
{
    // M[i] = i^2
    size_t dim_count = 1;
    size_t dims[] = {6};
    struct matrix *m1 = matrix_init(dim_count, dims);
    size_t pos[1];
    int i;
    for (i = 1; i <= 6; i++) {
        pos[0] = i;
        matrix_set_element(m1, pos, i*i);
    }
    matrix_print_metadata(m1);
    matrix_print(m1);
    matrix_destroy(m1);
    return 0;
}

int matrix_2D_test2()
{
    // M[i,j] = 2*i + j^2
    size_t dim_count = 2;
    size_t dims[] = {6,3};
    struct matrix *m1 = matrix_init(dim_count, dims);
    size_t pos[2];
    int i, j;
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 3; j++) {
            pos[0] = i;
            pos[1] = j;
            matrix_set_element(m1, pos, 2*i + j*j);
        }
    }
    matrix_print_metadata(m1);
    matrix_print(m1);
    matrix_destroy(m1);
    return 0;
}

int matrix_1D_test2()
{
    // M[i] = sin(t[i]) for t = 0:pi/100:pi
    struct matrix *t = matrix_linspace(0, MATRIX_PI, 10); // -> produces 101 numbers
    size_t dim_count = 1;
    printf("t: \n");
    matrix_print_metadata(t);
    matrix_print(t);
    struct matrix *m1 = matrix_init_labels(dim_count, &t);
    // struct matrix *result1 = matrix_sin(m1);
    printf("\nm1: \n");
    matrix_print_metadata(m1);
    matrix_print(m1);
    // printf("matrix_sin(m1) = \n");
    // matrix_print_metadata(result1);
    // printf("\n");
    // matrix_print(result1);
    // matrix_destroy_batch(3, result1, m1, t);
    matrix_destroy_batch(2, m1, t);
    return 0;
}

int main()
{
    // matrix_1D_test1();
    // matrix_2D_test2();
    matrix_1D_test2();
    return 0;
}