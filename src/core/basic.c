#include "matrix.h"

struct matrix *matrix_transpose(struct matrix *A)
{
	struct matrix *AT = matrix_dup(A);
	// putting rows of A into columns of AT
	size_t M = A->dims[0], N = A->dims[1];
	size_t i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			AT->e[i*N + j] = A->e[j*M + i]; // isn't it beautiful?! xD
		}
	}
	AT->dims[0] = A->dims[1];
	AT->dims[1] = A->dims[0];
	return AT;
}