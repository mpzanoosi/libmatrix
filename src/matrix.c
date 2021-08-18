#include "matrix.h"
#include "mm.h"

int _factorial(size_t count, size_t *intvals)
{
    size_t i, result = 1;
    for (i = 0; i < count; i++) {
        result *= intvals[i];
    }
    return result;
}

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims)
{
    structinit(struct matrix, new_matrix);
    new_matrix->dim_count = dim_count;
    ptrccpy(new_matrix->dims, dims, size_t, dim_count);
    new_matrix->dims_all = _factorial(dim_count, dims);
    new_matrix->values = (double *)calloc(new_matrix->dims_all, sizeof(double));
    new_matrix->labels = NULL;
    return new_matrix;
}

int matrix_destroy(struct matrix *m)
{
    if (!m)
        return 0;
    
    free_safe(m->labels);
    free_safe(m->values);
    free_safe(m->dims);
    free_safe(m);
    // why Mr. Anderson, why?!
    
    return 0;
}

char *_array_strval_size_t(size_t count, size_t *a)
{
    if (!a) {
        return strdup("[]");
    }

    char temp[20] = {0};
    char *strval = strdup("[");
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%zu, ", a[i]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%zu]", a[count-1]);
    strcat(strval, temp);
    return strval;
}

char *_array_strval_double(size_t count, double *a)
{
    if (!a) {
        return strdup("[]");
    }

    char temp[20] = {0};
    char *strval = strdup("[");
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%f, ", a[i]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%f]", a[count-1]);
    strcat(strval, temp);
    return strval;
}

char *_matrix_strval_metadata(struct matrix *m, char *delimiter)
{
    // fixme: what if metadata string goes beyond 1000 bytes?!
    char *strval = (char *)malloc(1000);
    char *temp = (char *)malloc(100);
    char *temp2;

    memreset(temp, 100);
    sprintf(temp, "%sdim_count = %zu%s", delimiter, m->dim_count, delimiter);
    strcat(strval, temp);

    memreset(temp, 100);
    temp2 = _array_strval_size_t(m->dim_count, m->dims);
    sprintf(temp, "dims = %s%s", temp2, delimiter);
    free_safe(temp2);
    strcat(strval, temp);

    memreset(temp, 100);
    temp2 = _array_strval_double(m->dim_count, m->labels);
    sprintf(temp, "labels = %s%s", temp2, delimiter);
    free_safe(temp2);
    strcat(strval, temp);

    free_safe(temp);
    return strval;
}

char *matrix_strval_metadata(struct matrix *m)
{
    return _matrix_strval_metadata(m, "");
}

void matrix_print_metadata_(struct matrix *m, char *name)
{
    char *strval = _matrix_strval_metadata(m, "\n\t");
    printf("%s metadata:%s\n", name, strval);
    free_safe(strval);
}