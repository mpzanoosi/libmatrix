#ifndef MATRIX_INIT_H
#define MATRIX_INIT_H

#include "mm.h"
#include "vidx.h"
#include "array.h"

/** 
 * private declarations are here: it is only for internal
 * usage; they are not supposed to be on public headers
 */

struct matrix;

void _matrix_e2_update(struct matrix *m);

#endif // MATRIX_INIT_H