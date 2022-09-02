#include "../src/core/matrix.h"

void test_matrix_init()
{
    size_t dim_count = 2;
    size_t dims[2] = {3,6};
    struct matrix *A = matrix_init(dim_count, dims);
    int i;
    matrix_for_each_element(i, A) {
        A->e[i] = i;
    }
    matrix_print_all(A);
}

int main()
{
    test_matrix_init(); // testing matrix init.c
    return 0;
}