#include "matrix.h"

struct matrix *matrix_dup(struct matrix *A)
{
	// making a duplicate without considering pointers contents
	struct matrix *A_copy = structdup(A);

	// making duplicate out of pointers contents
	ptrccpy(A_copy->dims, A->dims, size_t, A->dim_count);
	if (A->e_count > 0) {
		ptrccpy(A_copy->e, A->e, double, A->e_count);
	}

	return A_copy;
}