#include "../src/core/matrix.h"

void test_matrix_init()
{
    // making a new matrix
    size_t dim_count = 2;
    size_t dims[2] = {3,6};
    struct matrix *A = matrix_init(dim_count, dims);

    // filling the matrix
    int i;
    matrix_for_each_element(i, A) {
        A->e[i] = (double)i;
    }

    // printing all information of the matrix
    matrix_print_all(A);

    // iterating a row 
    int j, r = 2;
    printf("row #%d: ", r);
    matrix_for_each_x_in_row(j, A, r) {
        printf("%f, ", A->e[j]);
    }
    printf("\n");
    
    // iterating a column 
    int c = 4;
    printf("col #%d: ", c);
    matrix_for_each_x_in_col(i, A, c) {
        printf("%f, ", A->e[i]);
    }
    printf("\n");

    // freeing the memory
    matrix_destroy(A);
}

int main()
{
    test_matrix_init(); // testing matrix init.c
    return 0;
}