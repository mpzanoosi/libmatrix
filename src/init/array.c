#include "array.h"
#include "mm.h"

// ***** array calculations ***** //

size_t matrix_array_pimult(size_t count, size_t *intvals)
{
    if (count < 0)
        return -1;
        
    if (count == 0)
        return 1;

    size_t i, result = 1;
    for (i = 0; i < count; i++) {
        result *= intvals[i];
    }
    return result;
}

size_t matrix_array_sigmasum(size_t count, size_t *intvals)
{
    if (count < 0)
        return -1;

    if (count == 0)
        return 0;

    size_t i, result = 0;
    for (i = 0; i < count; i++) {
        result += intvals[i];
    }
    return result;
}

// ***** array stringifying ***** //

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

char *matrix_array_strval_double_vidxs(double *a, size_t *vidxs, size_t count)
{
    if (!a || count < 1) {
        return strdup("");
    }

    // exactly same as array_strval, but indexes are not 
    // typical 0, 1, ..., count-1; instead the indexes are stored
    // in vidxs[0], vidxs[1], ..., vidxs[count-1]

    char *strval; // output of this function
    char temp[50]; // for holding a number

    strval = (char *)calloc(32*count + (count-1), sizeof(char));
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, STR(_strval_double_format)", ", a[vidxs[i]]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, STR(_strval_double_format), a[vidxs[count-1]]);
    strcat(strval, temp);
    return strval;
}