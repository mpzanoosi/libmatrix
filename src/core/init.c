#include "matrix.h"
#include "array.h"

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

// making strings and printing
#define _STR(x) #x
#define STR(x) _STR(x)
#define PREC MATRIX_DOUBLE_PREC
#define EVALUATOR(x) x
#define _strval_double_format %.EVALUATOR(PREC)f
#define _strva_sizet_format %zu

char *matrix_strval(struct matrix *m)
{
    // making string out of 2D matrix
    // style: 
    // e11,e12,...,e1N
    // e21,e22,...,e2N
    // ...
    // eM1,eM2,...,eMN
    // 
    // - DBL_MAX_10_EXP+2 bytes for each element plus ',' and '\n' character for each row
	//   and the string terminator '\0' at the end
    //   so in (total DBL_MAX_10_EXP+3)*e_count + 1*row_count + 1
	
    char *strval;
    size_t needed_bytes_count = (DBL_MAX_10_EXP+3) * m->e_count + m->dims[0] + 1;
    strval = (char *)calloc(needed_bytes_count, sizeof(char));

	int r, j; // iterators for row and elements of a row
	double x;
    char temp[DBL_MAX_10_EXP+2]; // for holding a number
	matrix_for_each_row(r, m) {
		matrix_for_each_x_in_row(j, m, r, x) {
			memreset(temp, sizeof(temp));
			sprintf(temp, STR(_strval_double_format)", ", x);
			strcat(strval, temp);
		}
		strcat(strval, "\n"); // removing last ',' and putting '\n' in the end
	}

    strval[strlen(strval)-1] = '\0'; // string terminator
    return strval;
}

void matrix_print(struct matrix *m)
{
    char *strval = matrix_strval(m);
    printf("%s\n", strval);
    free_safe(strval);
}

char *matrix_strval_metadata(struct matrix *m)
{
    // fixme: what if metadata string goes beyond 1000 bytes?!
    // fixme: what if temp goes beyond 100 bytes?!
    // confusion of the highest orda!
    char *strval = (char *)calloc(1000, sizeof(char));
    char temp[100];
    char *temp2;

    // dim_count
    memreset(temp, sizeof(temp));
    sprintf(temp, "dim_count = %zu\n", m->dim_count);
    strcat(strval, temp);

    // dims
    memreset(temp, sizeof(temp));
    temp2 = matrix_array_strval_size_t(m->dims, m->dim_count);
    sprintf(temp, "dims = [%s]\n", temp2);
    free_safe(temp2);
    strcat(strval, temp);
    
    // e_count
    memreset(temp, sizeof(temp));
    sprintf(temp, "e_count = %zu\n", m->e_count);
    strcat(strval, temp);
    
    return strval;
}

void matrix_print_metadata(struct matrix *m)
{
    char *strval = matrix_strval_metadata(m);
    printf("%s", strval);
    free_safe(strval);
}