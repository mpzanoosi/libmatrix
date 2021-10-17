#include "basics.h"
#include "../init/init.h"
#include "../init/vidx.h"

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
        size_t i, j;
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                mT->e[i*N + j] = m->e[j*M + i]; // isn't it beautiful?! xD
            }
        }
        mT->dims[0] = N;
        mT->dims[1] = M;
        _matrix_update_e2(mT);
        // transposing labels as well
        if (m->l_count > 0) {
            for (i = 0; i < M; i++)
                mT->l[N+i] = m->l[i];
            for (i = 0; i < N; i++)
                mT->l[i] = m->l[M+i];
        }
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
    size_t new_e_count = matrix_array_pimult(new_dim_count, new_dims);
    if (new_e_count != m->e_count)
        return NULL;

    // reshaping is very easy xD
    struct matrix *result = matrix_dup(m);
    result->dim_count = new_dim_count;
    free_safe(result->dims);
    ptrccpy(result->dims, new_dims, size_t, new_dim_count);
    if (new_dim_count == 2) {
        _matrix_update_e2(result);
    }

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

double _matrix_det_2x2(double *e)
{
    return (e[0]*e[3] - e[1]*e[2]);
}

void _matrix_get_conjmatrix(double *e_conj, size_t N, double *e, size_t row, size_t col)
{
    // returning conjugate matrix: matrix of removing ith row and jth column
    // of a reference matrix 'e'
    // note that reference matrix 'e' and the result conjugate matrix
    // 'e_conj' both are memory-allocated and vectorized
    
    size_t i, j, k = 0;
    size_t vidx;
    for (j = 1; j <= N; j++) {
        for (i = 1; i <= N; i++) {
            if (i != row && j != col) {
                vidx = matrix_pos2vidx_2d_square(N, i, j);
                e_conj[k] = e[vidx];
                k++;
            }
        }
    }
}

double _matrix_det_NxN(size_t N, double *e)
{
    // purpose of this internal function is:
    // 1. calling this function recursively
    // 2. avoid extra checking in matrix_det at each recursion

    if (N == 2)
        return _matrix_det_2x2(e);
    
    size_t i;
    double sgn = +1;
    double det = 0, temp;
    double *e_conj = (double *)calloc((N-1)*(N-1), sizeof(double));
    for (i = 1; i <= N; i++) {
        _matrix_get_conjmatrix(e_conj, N, e, i, 1);
        temp = _matrix_det_NxN(N-1, e_conj);
        det = det + sgn * e[i-1] * temp;
        sgn = -sgn;
    }
    free_safe(e_conj);
    return det;
}

double matrix_det(struct matrix *m)
{
    // determinant is only defined for square 2D matrices
    // if we assume a number is a 1x1 2D matrix,
    // so the determinant would be the same as the
    // number

    if (matrix_issquare(m) != 0)
        return -1;
    
    // higher dimensional matrices require more calculations
    double det;
    if (m->dims[0] > 2)
        det = _matrix_det_NxN(m->dims[0], m->e);
    
    // determinant of a 2x2 matrix is easy
    if (m->dims[0] == 2)
        return _matrix_det_2x2(m->e);

    // determinant of a single element matrix is that number
    if (m->e_count == 1)
        return m->e[0];

    return det;
}
