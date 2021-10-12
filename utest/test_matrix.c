#include "../src/init/matrix.h" // -> <matrix/matrix.h>
#include "../src/init/array.h" // -> <matrix/array.h>
#include "../src/basics/basics.h" // -> <matrix/basics.h>
#include "../src/funcs/funcs.h" // -> <matrix/funcs.h>

int test1_1D()
{
    // A[i] = i^2
    size_t dim_count = 1;
    size_t dims[] = {6};
    struct matrix *A = matrix_init(dim_count, dims);
    size_t pos[1];
    int i;
    for (i = 1; i <= 6; i++) {
        pos[0] = i;
        matrix_set_element(A, pos, i*i);
    }
    matrix_print_metadata(A);
    matrix_print(A);
    matrix_destroy(A);
    return 0;
}

int test1_2D()
{
    // A[i,j] = 2*i + j^2
    size_t dim_count = 2;
    size_t dims[] = {6,3};
    struct matrix *A = matrix_init(dim_count, dims);
    size_t pos[2];
    int i, j;
    for (i = 1; i <= 6; i++) {
        for (j = 1; j <= 3; j++) {
            pos[0] = i;
            pos[1] = j;
            matrix_set_element(A, pos, 2*i + j*j);
        }
    }
    matrix_print_metadata(A);
    matrix_print(A);
    matrix_destroy(A);
    return 0;
}

int test2_1D()
{
    // A[i] = sin(t[i]) for t = 0:pi/10:pi
    struct matrix *t = matrix_linspace(0, MATRIX_PI, 10);
    struct matrix *A = matrix_sin(t);
    matrix_print_all(t);
    matrix_print_all(A);
    matrix_destroy_batch(2, t, A);
    return 0;
}

int test2_2D()
{
    // A(x,y) = sin(x) * cos(y) === A[i,j] = sin(x[i])*cos(y[j])
    struct matrix *x = matrix_sin_linspace(0, MATRIX_PI, 10);
    struct matrix *y = matrix_cos_range(0, 30, 5);
    struct matrix *A = matrix_crossproduct(y, x);
    matrix_print_all(A);
    matrix_destroy_batch(3, x, y, A);
    return 0;
}

int test_operators()
{
    // testing matrix_reshape
    printf("---- testing matrix_reshape ----\n");
    struct matrix *A = matrix_sin_linspace(0, MATRIX_PI, 18);
    size_t new_dims[] = {6,3};
    struct matrix *A1 = matrix_reshape(A, 2, new_dims);
    size_t new_dims2[] = {2,9};
    struct matrix *A2 = matrix_reshape(A1, 2, new_dims2);
    matrix_print_all(A);
    matrix_print_all(A1);
    matrix_print_all(A2);

    // testing matrix_transpose
    printf("\n---- testing matrix_transpose ----\n");
    struct matrix *A1T = matrix_transpose(A1);
    matrix_print_all(A1);
    matrix_print_all(A1T);

    matrix_destroy_batch(4, A, A1, A2, A1T);
    return 0;
}

int main()
{
    test1_1D();
    test1_2D();
    test2_1D();
    test2_2D();
    test_operators();
    return 0;
}