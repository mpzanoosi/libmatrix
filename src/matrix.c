#include "matrix.h"
#include "helper.h"
#include "mm.h"
#include "array.h"
#include "vidx.h"

// ***** core methods ***** //

struct matrix *matrix_init_empty(size_t dim_count, size_t *dims)
{
    structinit(struct matrix, new_matrix);
    new_matrix->dim_count = dim_count;
    ptrccpy(new_matrix->dims, dims, size_t, dim_count);
    new_matrix->e_count = helper_pimult(dim_count, dims);
    new_matrix->values = (double *)calloc(new_matrix->e_count, sizeof(double));
    new_matrix->labels = (double **)calloc(dim_count, sizeof(double *));
    // "he is beginning to believe"
    return new_matrix;
}

struct matrix *matrix_init_empty_labels(size_t dim_count, struct matrix **ranges)
{
    // making an empty matrix with dimensions based on 
    // elements of each range
    // each range is supposed to be the label of each
    // dimension

    // making an empty matrix with proper dimensions
    size_t *dims = (size_t *)calloc(dim_count, sizeof(size_t));
    size_t i;
    for (i = 0; i < dim_count; i++) {
        dims[i] = ranges[i]->e_count;
    }
    struct matrix *new_matrix = matrix_init_empty(dim_count, dims);
    free_safe(dims);
    // now setting labels of the new matrix based on each range
    for (i = 0; i < dim_count; i++) {
        matrix_set_label_by_range(new_matrix, i, ranges[i]);
    }
    return new_matrix;
}

int matrix_destroy(struct matrix *m)
{
    if (!m)
        return 0;
    
    size_t i;
    for (i = 0; i < m->dim_count; i++) {
        free_safe(m->labels[i]);
    }
    free_safe(m->labels);
    free_safe(m->values);
    free_safe(m->dims);
    free_safe(m);
    // why Mr. Anderson, why?!
    return 0;
}

int matrix_set_value(struct matrix *m, size_t *pos, double value)
{
    size_t vidx = vidx_pos(m, pos);
    if (vidx == -1)
        return -1;
    m->values[vidx] = value;
    return 0;
}

int matrix_set_label(struct matrix *m, size_t dim, double *label)
{
    ptrccpy(m->labels[dim], label, double, m->dims[dim]);
    return 0;
}

int matrix_set_label_by_range(struct matrix *m, size_t dim, struct matrix *range)
{
    return matrix_set_label(m, dim, range->values);
}

struct matrix *matrix_range(double x1, double x2, double dx)
{
    size_t count = ceil((x2-x1)/dx) + 1;
    if (count < 1)
        return NULL;

    size_t dim_count = 1;
    size_t dims[1];
    dims[0] = count;
    struct matrix *m = matrix_init_empty(dim_count, dims);
    size_t i = 0;
    double last_value = x1;
    do {
        m->values[i] = last_value;
        last_value += dx;
        i++;
    } while (i < count);
    return m;
}

struct matrix *matrix_linspace(double x1, double x2, size_t count)
{
    return matrix_range(x1, x2, (x2-x1)/(count-1));
}

// ***** printing and stringifying ***** //

char *matrix_strval_2d(struct matrix *m)
{
    char *strval; // output of this function

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

    char *line; // temporary memory for each line
    size_t M = m->dims[0], N = m->dims[1];
    size_t *vidxs = (size_t *)malloc(N * sizeof(size_t));
    size_t i;
    for (i = 1; i <= M; i++) {
        vidx_row_2d(m, i, vidxs);
        line = array_strval_vidxs(m->values, vidxs, N);
        strcat(strval, line);
        strcat(strval, "\n");
        free_safe(line);
    }
    strval[strlen(strval)-1] = '\0';
    free_safe(vidxs);
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
        strval = array_strval(m->values, m->e_count);
    } else if (m->dim_count == 2) {
        // making string out of a 2D matrix
        strval = matrix_strval_2d(m);
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
        size_t extra_dims_counts = helper_pimult(m->dim_count-2, m->dims+2);
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
    char *strval = (char *)malloc(1000);
    char temp[100];
    char *temp2, *temp3;

    // dim_count
    memreset(temp, 100);
    sprintf(temp, "dim_count = %zu\n", m->dim_count);
    strcat(strval, temp);

    // dims
    memreset(temp, 100);
    temp2 = array_strval_size_t(m->dims, m->dim_count);
    sprintf(temp, "dims = [%s]\n", temp2);
    free_safe(temp2);
    strcat(strval, temp);

    // labels
    size_t i;
    for (i = 0; i < m->dim_count; i++) {
        if (m->labels[i]) {
            temp2 = array_strval(m->labels[i], m->dims[i]);
            temp3 = (char *)calloc(100 + strlen(temp2), sizeof(char));
            sprintf(temp3, "labels[%zu] = [%s]\n", i, temp2);
            free_safe(temp2);
            strcat(strval, temp3);
            free_safe(temp3);
        } else {
            sprintf(temp, "labels[%zu] = []\n", i);
            strcat(strval, temp);
        }
    }
    return strval;
}

void matrix_print_metadata(struct matrix *m)
{
    char *strval = matrix_strval_metadata(m);
    printf("%s", strval);
    free_safe(strval);
}