#include "matrix.h"

struct matrix *matrix_init_empty(size_t dim_count, size_t *counts)
{
    structinit(struct matrix, new_matrix);
    structinit(struct set, labels);
    labels->dim_count = dim_count;
    labels->
    new_matrix->labels = structdup(labels);
    new_matrix->values = (double *)calloc(labels->counts_all, sizeof(double));
    return new_matrix;
}

struct matrix *matrix_init_empty(struct set *labels)
{
    structinit(struct matrix, new_matrix);
    new_matrix->labels = structdup(labels);
    new_matrix->values = (double *)calloc(labels->counts_all, sizeof(double));
    return new_matrix;
}

int matrix_arrayidx(struct set *labels, int *pos)
{
    // examples of MxN matrix:
    //  pos(1,1) => 0
    //  pos(2,1) => 1
    //  ...
    //  pos(M,1) => M-1
    //  pos(1,2) => 0 + (2-1)*M
    //  pos(2,2) => 1 + (2-1)*M
    //  ...
    //  pos(M,2) => M-1 + (2-1)*M
    //  ...
    //  pos(i,j) => (i-1) + (j-1)*N
    //  ...
    //  pos(M,N) => (M-1) + (N-1)*N
    
    int idx = 0;
    int i;
    for (i = 0; i < labels->dim_count; i++) {
        idx = idx + ???;
    }
}

int matrix_insert(struct matrix *this, int *pos, double value)
{
    int idx = matrix_arrayidx(this->labels, pos_counts, pos);
    this->values[idx] = value;
    return 0;
}