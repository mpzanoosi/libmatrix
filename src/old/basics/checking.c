#include "basics.h"
#include "../init/init.h"

int matrix_issquare(struct matrix *m)
{
    // sqaure matrix checking can only be done
    // on 2D matrices

    if (m->dim_count == 2)
        if (m->dims[0] == m->dims[1])
            return 0;

    // a matrix with 1 element is a square matrix
    if (m->e_count == 1)
        return 0;

    return -1;
}