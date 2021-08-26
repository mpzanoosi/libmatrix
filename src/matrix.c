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

int matrix_set_value(struct matrix *m, size_t *pos, double value)
{
    size_t vidx = vidx_pos(m, pos);
    if (vidx == -1)
        return -1;
    m->values[vidx] = value;
    return 0;
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
    char *strval = (char *)malloc(1000);
    char *temp = (char *)malloc(100);
    char *temp2;

    memreset(temp, 100);
    sprintf(temp, "dim_count = %zu\n", m->dim_count);
    strcat(strval, temp);

    memreset(temp, 100);
    temp2 = array_strval_size_t(m->dims, m->dim_count);
    sprintf(temp, "dims = [%s]\n", temp2);
    free_safe(temp2);
    strcat(strval, temp);

    memreset(temp, 100);
    temp2 = array_strval(m->labels, m->dim_count);
    sprintf(temp, "labels = [%s]", temp2);
    free_safe(temp2);
    strcat(strval, temp);

    free_safe(temp);
    return strval;
}

void matrix_print_metadata(struct matrix *m)
{
    char *strval = matrix_strval_metadata(m);
    printf("%s\n", strval);
    free_safe(strval);
}