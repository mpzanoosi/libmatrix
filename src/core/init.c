#include "matrix.h"

// init
struct matrix *matrix_init(size_t dim_count, size_t *dims)
{
	// allocating a new matrix struct
	structalloc(struct matrix, new_matrix);
	new_matrix->dim_count = dim_count;
	ptrccpy(new_matrix->dims, dims, size_t, dim_count);
	// allocating memory for elements
	new_matrix->e_count = matrix_array_mul(dim_count, dims);
	new_matrix->e = (double *)calloc(new_matrix->e_count, sizeof(double));
	return new_matrix; // he is beginning to believe!
}

int matrix_destroy(struct matrix *A)
{
	if (!A)
		return 0;
	// freeing allocated memories
	free_safe(A->e);
	free_safe(A->dims);
	free_safe(A);
	return 0; // how long this peace is going to last?!
}

int matrix_destroy_batch(int count, ...)
{
	struct matrix *A;
	int i;
	va_list ap;
	// loop to destroy all 
	va_start(ap, count);
	for (i = 0; i < count; i++) {
		A = va_arg(ap, struct matrix *);
		matrix_destroy(A);
	}
	va_end(ap);
	return 0;
}