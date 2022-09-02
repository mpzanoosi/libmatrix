#include "matrix.h"

#define _STR(x) #x
#define STR(x) _STR(x)
#define PREC MATRIX_DOUBLE_PREC

#define EVALUATOR(x) x
#define _strval_double_format %.EVALUATOR(PREC)f

#define _strva_sizet_format %zu

// making string out of a 1D matrix = an array
// style: 
// 
// for each double we reserve 32 bytes
// there is count-1 extra characters for space characters
// (characters between numbers)
// 
// IMPORTANT NOTE: are 50 bytes for temp and 32 bytes for holding a double enough?
// answer: NO! it should be handled generally
//         google "double maximum string size" and see stackoverflow why!
//         however, the answer in that stackoverflow seems to be wrong!!!
//         this is a floating point representation issue.
// notes:
// char *strval; // output of this function
// char temp[50]; // for holding a number
#define _matrix_array_strval_by_format(type, a, count, format)\
    if (!a || count < 1) {\
        return strdup("");\
    }\
    char *strval;\
    char temp[50];\
    strval = (char *)calloc(32*count + (count-1), sizeof(char));\
    int i;\
    for (i = 0; i < count-1; i++) {\
        memreset(temp, sizeof(temp));\
        sprintf(temp, format", ", a[i]);\
        strcat(strval, temp);\
    }\
    memreset(temp, sizeof(temp));\
    sprintf(temp, format, a[count-1]);\
    strcat(strval, temp);\
    return strval;\

char *matrix_array_strval_double(double *a, size_t count)
{
    _matrix_array_strval_by_format(double, a, count, STR(_strval_double_format));
}

char *matrix_array_strval_size_t(size_t *a, size_t count)
{
    _matrix_array_strval_by_format(size_t, a, count, STR(_strva_sizet_format));
}

size_t matrix_array_mul(size_t count, size_t *a)
{
    size_t i;
    size_t result = 1;
    for (i = 0; i < count; i++) {
        result *= a[i];
    }
    return result;
}