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
    if (!a || count < 1) {
        return strdup("");
    }

    char *strval; // output of this function
    char temp[50]; // for holding a number

    // making string out of an 1D matrix = an array
    // style: e1,e2,...,eN
    //        for each double we reserve 32 bytes
    //        there is count-1 extra characters for ',' characters
    // 
    // IMPORTANT NOTE: are 50 bytes for temp and 32 bytes for holding a double enough?
    // answer: NO! it should be handled generally
    //         google "double maximum string size" and see stackoverflow why!
    //         however, the answer in that stackoverflow seems to be wrong!!!
    strval = (char *)malloc(32*count + (count-1));
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%zu,", a[i]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%zu", a[count-1]);
    strcat(strval, temp);
    return strval;
}

char *_array_strval(double *a, size_t count)
{
    if (!a || count < 1) {
        return strdup("");
    }

    char *strval; // output of this function
    char temp[50]; // for holding a number

    // making string out of an 1D matrix = an array
    // style: 
    // 
    // for each double we reserve 32 bytes
    // there is count-1 extra characters for ',' characters
    // 
    // IMPORTANT NOTE: are 50 bytes for temp and 32 bytes for holding a double enough?
    // answer: NO! it should be handled generally
    //         google "double maximum string size" and see stackoverflow why!
    //         however, the answer in that stackoverflow seems to be wrong!!!
    strval = (char *)malloc(32*count + (count-1));
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%f,", a[i]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%f", a[count-1]);
    strcat(strval, temp);
    return strval;
}

char *_array_strval_idxs(double *a, size_t *idxs, size_t count)
{

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
    temp2 = _array_strval_size_t(m->dims, m->dim_count);
    sprintf(temp, "dims = [%s]%s", temp2, delimiter);
    free_safe(temp2);
    strcat(strval, temp);

    memreset(temp, 100);
    temp2 = _array_strval(m->labels, m->dim_count);
    sprintf(temp, "labels = [%s]%s", temp2, delimiter);
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

void matrix_get_vidxs_row(struct matrix *m, size_t row, size_t *idxs)
{

}

char *_matrix_strval_2d(struct matrix *m)
{
    char *strval; // output of this function
    char *line; // for each line

    // making string out of 2D matrix
    // style: 
    // e11,e12,...,e1N
    // e21,e22,...,e2N
    // ...
    // eM1,eM2,...,eMN
    // 
    // - 32+1 bytes for each element including ',' and end of line '\n' characters
    //   todo question: is 32+1 bytes sufficient?!
    size_t needed_bytes = (32+1) * m->e_count;
    strval = (char *)malloc(needed_bytes);
    size_t M = m->dims[0], N = m->dims[1];
    size_t *idxs = (size_t *)malloc(N * sizeof(size_t));
    size_t i;
    for (i = 1; i < M; i++) {
        matrix_get_vidxs_row(m, i, idxs);
        line = _array_strval_idxs(m->values, idxs, N);
        strcat(strval, line);
        free_safe(line);
    }
    return strval;
}

char *matrix_strval(struct matrix *m)
{
    char *strval; // output of this function
    char temp[50]; // for holding a number

    if (m->dim_count < 1) {
        strval = strdup("");
    } else if (m->dim_count == 1) {
        // making string out of a 1D matrix = an array
        strval = _array_strval(m->values, m->e_count);
    } else if (m->dim_count == 2) {
        // making string out of a 2D matrix
        strval = _matrix_strval_2d(m);
    } else {
        // example:
        // needed bytes for matirx with dims = [3,4,5,6]:
        //  - each element should have size of double + 1 space
        //  - we must show 5*6 2D matrix of size [3,4]
        //      -- each 2D matrix should have 3 extra bytes for 
        //         '\n' character at the end of each row
        //      -- between each 2D matrix, we print "(:,:,i,j):\n":
        //         so we need extra (5*6-1)*(9+2*sizeof(size_t)) characters
        //         9 = number of characters of "(:,:,,):\n"
        //  - we add 10 bytes just for a margin (not necessary, but just to make sure)
        //
        // a way to calculate 5*6 :D
        size_t extra_dims_counts = _pimult(m->dim_count-2, m->dims+2);
        size_t needed_bytes = \
            /*bytes for each element*/ (sizeof(double)+1) * m->e_count + \
            /*bytes for '\n' characters*/ extra_dims_counts * m->dims[0] + \
            /*bytes for between 2D matrix separators*/ (extra_dims_counts-1) * (9+2*sizeof(size_t)) +\
            /*margin bytes*/ 10;
        strval = (char *)malloc(needed_bytes);

        size_t line_length = (sizeof(double)+1) * m->dims[1] + 5; // 5 is just for margin
        char *line = (char *)malloc(line_length);
        size_t separator_length = 9+2*sizeof(size_t) + 5; // 5 is just for margin
        char *separator = (char *)malloc(separator_length);
        
        int i;
        for (i = 0; i < extra_dims_counts; i++) {
            memreset(separator, separator_length);
            // todo: fill this loop
        }
    }
    return strval;
}

void matrix_print_(struct matrix *m, char *name)
{
    char *strval = matrix_strval(m);
    printf("%s:\n%s\n", name, strval);
    free_safe(strval);
}
