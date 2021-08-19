#include "matrix.h"
#include "mm.h"

// ***** core methods ***** //

size_t _pimult(size_t count, size_t *intvals)
{
    if (count == 0)
        return 1;

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
    new_matrix->e_count = _pimult(dim_count, dims);
    new_matrix->values = (double *)calloc(new_matrix->e_count, sizeof(double));
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

size_t matrix_get_vidx(struct matrix *m, size_t *pos)
{
    // dims = [3,4,5]
    // pos = [1,2,3]
    // => vidx = (1-1) + (2-1)*3 + (3-1)*(3*4)
    // algorithm: if you want to step in i-th dimension,
    //  you should add elements count of all previous
    //  dimensions by each step
    //  (pos[i]-1) -> number of steps
    //  _pimult(i, m->dims) -> number of passed elements per step in the i-th dimension
    size_t vidx = 0;
    int i;
    for (i = 0; i < m->dim_count; i++) {
        vidx += (pos[i]-1) * _pimult(i, m->dims);
    }
    return vidx;
}

int matrix_set_value(struct matrix *m, size_t *pos, double value)
{
    size_t idx = matrix_get_vidx(m, pos);
    if (idx == -1)
        return -1;
    m->values[idx] = value;
    return 0;
}

// ***** printing and stringifying ***** //

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

char *matrix_strval(struct matrix *m)
{
    // needed bytes for [3,4,5,6]:
    //  - each element should have size of double + 1 space
    //  - we must show 5*6 2D matrix of size [3,4]
    //      -- each 2D matrix should have 3 extra bytes for 
    //         '\n' character at the end of each row
    //      -- between each 2D matrix, we print "(:,:,i,j):\n":
    //         so we need extra (5*6-1)*(9+2*sizeof(size_t)) characters
    //  - we add 10 bytes just for a margin (not necessary, but just to make sure)

    size_t extra_dims_counts;
    if (m->dim_count > 2) {
        // a way to calculate 5*6 :D
        extra_dims_counts = _pimult(m->dim_count-2, m->dims+(size_t)2);
    } else {
        extra_dims_counts = 1;
    }

    size_t needed_bytes = \
        /*bytes for each element*/ (sizeof(double)+1) * m->e_count + \
        /*bytes for '\n' characters*/ extra_dims_counts * m->dims[0] + \
        /*bytes for between 2D matrix separators*/ (extra_dims_counts-1) * (9+2*sizeof(size_t)) +\
        /*margin bytes*/ 10;
    char *strval = (char *)malloc(needed_bytes);

    // todo: making string depends on (dim_count > 2) ? :

    size_t line_length = (sizeof(double)+1) * m->dims[1] + 5; // 5 is just for margin
    char *line = (char *)malloc(line_length);
    size_t separator_length = 9+2*sizeof(size_t) + 5; // 5 is just for margin
    char *separator = (char *)malloc(separator_length);
    
    int i;
    for (i = 0; i < extra_dims_counts; i++) {
        memreset(separator, separator_length);
    }
}

void matrix_print_(struct matrix *m, char *name);
