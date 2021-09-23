#include "array.h"

#define _STR(x) #x
#define STR(x) _STR(x)
#define PREC 2

char *array_strval(double *a, size_t count)
{
    if (!a || count < 1) {
        return strdup("");
    }

    char *strval; // output of this function
    char temp[50]; // for holding a number

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
    strval = (char *)calloc(32*count + (count-1), sizeof(char));
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%." STR(PREC) "f, ", a[i]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%." STR(PREC) "f", a[count-1]);
    strcat(strval, temp);
    return strval;
}

char *array_strval_size_t(size_t *a, size_t count)
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
    strval = (char *)calloc(32*count + (count-1), sizeof(char));
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


char *array_strval_vidxs(double *a, size_t *vidxs, size_t count)
{
    if (!a || count < 1) {
        return strdup("");
    }

    // exactly same as array_strval, but indexes are not 
    // typical 0, 1, ..., count-1; instead the indexes are stored
    // in vidxs[0], vidxs[1], ..., vidxs[count-1]

    char *strval; // output of this function
    char temp[50]; // for holding a number

    strval = (char *)malloc(32*count + (count-1));
    int i;
    for (i = 0; i < count-1; i++) {
        memreset(temp, sizeof(temp));
        sprintf(temp, "%." STR(PREC) "f\t", a[vidxs[i]]);
        strcat(strval, temp);
    }
    memreset(temp, sizeof(temp));
    sprintf(temp, "%." STR(PREC) "f", a[vidxs[count-1]]);
    strcat(strval, temp);
    return strval;
}