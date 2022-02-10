#ifndef MATRIX_VIDX_H
#define MATRIX_VIDX_H

#include <stdlib.h>
#include "matrix.h"

// header to manipulate vectorized index concept
//
// what is vectorizing?
// appending matrix columns to each other, so there will be
// an array
// example:
//     e11,e12,...,e1N
//     e21,e22,...,e2N
//     ...
//     eM1,eM2,...,eMN
// after vectorizing: 
//     e11,e21,...,eM1,e12,e22,...,eM2,...,e1N,e2N,...,eMN
// 
// pos is the (i,j) position and vidx is its index in the 
// vectorized matrix

// converting matrix index to vidx
size_t matrix_pos2vidx(struct matrix *m, size_t *pos);

// same as matrix_pos2vidx but for 2D matrices
size_t matrix_pos2vidx_2d(struct matrix *m, size_t row, size_t col);

// same as matrix_pos2vidx_2d_square but for 2D sqaure matrices
size_t matrix_pos2vidx_2d_square(size_t N, size_t row, size_t col);

// getting all vidx numbers of a row for 2d
void matrix_row2vidxs_2d(struct matrix *m, size_t row, size_t *vidxs);

#endif // MATRIX_VIDX_H