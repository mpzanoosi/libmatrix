#include "matrix.h"
#include "helper.h"
#include "mm.h"
#include "vidx.h"

// single-element operators

struct matrix *matrix_transpose(struct matrix *m)
{
    // note: transpose works just for 1D and 2D matrices
    // question: shall it work for more than 2D?!
    // algorithm: transpose of
    //     e11,e12,...,e1N
    //     e21,e22,...,e2N
    //     ...
    //     eM1,eM2,...,eMN
    // is
    //     e11,e21,...,eM1
    //     e12,e22,...,eM2
    //     ...
    //     e1N,e2N,...,eMN
    // in vectorizing mode, transpose of 
    //     e11,e21,...,eM1,e12,e22,...,eM2,...,e1N,e2N,...,eMN
    // is
    //     e11,e12,...,e1N,e21,e22,...,e2N,...,eM1,eM2,...,eMN
    //
    // practical algorithm for 2D matrices:
    //     concatenate all rows with help of their vidx numbers

    if (m->dim_count < 1 || m->dim_count > 2)
        return NULL;
    
    struct matrix *mT = matrix_dup(m);

    // 1D transpose does not need to change anything
    // because our cross-product does not need something
    // to be 1x18 or 18x1
    // so we can ignore 1D matrices and just do for 2D
    // question: is above statements true?! I can't find
    //           any malfunctioning yet :D
    if (m->dim_count == 2) {
        size_t M = m->dims[0], N = m->dims[1];
        size_t i, j, vidx;
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                mT->e[i*N + j] = m->e[j*M + i]; // isn't it beautiful?! xD
            }
        }
        mT->dims[0] = N;
        mT->dims[1] = M;
    }

    return mT;
}

struct matrix *matrix_reshape(struct matrix *m, size_t new_dim_count, size_t *new_dims)
{
    // example: if m is a 6x3 matrix then new_dims should be
    //          something like [1,18], [9,2], ...;
    //          for example [4,5] is not possible
    // previous labels are not valid on the reshaped matrix

    // checking reshaping possibility by counting total elements
    size_t new_e_count = helper_pimult(new_dim_count, new_dims);
    if (new_e_count != m->e_count)
        return NULL;

    // reshaping is very easy xD
    struct matrix *result = matrix_dup(m);
    result->dim_count = new_dim_count;
    free_safe(result->dims);
    ptrccpy(result->dims, new_dims, size_t, new_dim_count);

    // previous labels no longer are valid
    free_safe(result->l);
    result->l_count = 0;

    return result;
}

// double-element operators

struct matrix *matrix_innerproduct(struct matrix *m1, struct matrix *m2)
{
    // note 1: inner-product is defined for vectors in a vector space
    // note 2: m1 and m2 are assumed to be equal dimension

    struct matrix *result = matrix_init(m1->dim_count, m1->dims);
    size_t i;
    for (i = 0; i < m1->e_count; i++) {
        result->e[i] = m1->e[i] * m2->e[i];
    }

    return result;
}

struct matrix *matrix_crossproduct(struct matrix *m1, struct matrix *m2)
{
    // note: cross-product is defined for vectors in a vector space

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