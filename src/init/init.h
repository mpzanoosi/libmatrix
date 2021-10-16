#ifndef MATRIX_INIT_H
#define MATRIX_INIT_H

#include "mm.h"
#include "vidx.h"
#include "array.h"

// more private functions to be used with other
// modules (like basics/)
struct matrix;

void _matrix_update_e2(struct matrix *m);

#endif // MATRIX_INIT_H