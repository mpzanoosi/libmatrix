#include "matrix.h"
#include "mm.h"

struct matrix *matrix_innerproduct(struct matrix *m1, struct matrix *m2)
{
    // m1 and m2 are assumed to be equal dimension
    struct matrix *result = matrix_init(m1->dim_count, m1->dims);
    size_t i;
    for (i = 0; i < m1->e_count; i++) {
        result->e[i] = m1->e[i] * m2->e[i];
    }

    return result;
}

struct matrix *matrix_crossproduct(struct matrix *m1, struct matrix *m2)
{
    // NOTE: for now, I just assume that both m1 and m2 are vectors
    // TODO: is there any cross product for general n-dimensional
    //       matrices?!

    size_t dim_count = 2;
    struct matrix *labels[2];
    labels[0] = m1;
    labels[1] = m2;
    struct matrix *result = matrix_init_labels(dim_count, labels);
    
    // filling elements based on cross product definition:
    // first column = first vector m1 * first element of second vector m2
    // and so on ...
    size_t i, j;
    for (j = 0; j < m2->e_count; j++) {
        for (i = 0; i < m1->e_count; i++) {
            result->e[j*m1->e_count + i] = m2->e[j] * m1->e[i];
        }
    }

    return result;
}