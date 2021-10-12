#include "vidx.h"
#include "array.h"

size_t vidx_pos(struct matrix *m, size_t *pos)
{
    // dims = [3,4,5]
    // pos = [1,2,3]
    // => vidx = (1-1) + (2-1)*3 + (3-1)*(3*4)
    // algorithm: if you want to step in i-th dimension,
    //  you should add elements count of all previous
    //  dimensions by each step
    //  (pos[i]-1) -> number of steps
    //  matrix_array_pimult(i, m->dims) -> number of passed elements per step in the i-th dimension
    size_t vidx = 0;
    int i;
    for (i = 0; i < m->dim_count; i++) {
        vidx += (pos[i]-1) * matrix_array_pimult(i, m->dims);
    }
    return vidx;
}

void vidx_row_2d(struct matrix *m, size_t row, size_t *vidxs)
{
    // storing vidx of a desired row in a vector
    size_t M = m->dims[0], N = m->dims[1];
    size_t j;
    for (j = 0; j < N; j++) {
        vidxs[j] = j*M + (row-1);
    }
}