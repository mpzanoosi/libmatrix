#include "array.h"
#include "file.h"

struct array *array_init_empty(size_t count)
{
    if (count < 1)
        return NULL;
    structinit(struct array, new_array);
    new_array->count = count;
    new_array->values = (double *)calloc(count, sizeof(double));
    return new_array;
}

struct array *array_init_range(double start, double end, double dx)
{
    size_t count = floor((end - start)/dx) + 1;
    if (count < 1)
        return NULL;

    // allocating and filling array object
    struct array *new_array = array_init_empty(count);
    int i = 0;
    double last_value = start;
    do {
        new_array->values[i] = last_value;
        last_value = last_value + dx;
        i++;
    } while ((dx > 0 && last_value <= end) || (dx < 0 && end <= last_value));

    return new_array;
}

int array_destroy(struct array *a)
{
    if (!a)
        return 0;

    if (a->count < 1) {
        free_safe(a);
        return 0;
    }
    
    free_safe(a->values);
    free_safe(a);
    return 0;
}

char *array_strval(struct array *a)
{
    char *strval;

    if (!a || a->count < 1) {
        strval = strdup("[]");
    } else {
        strval = strdup("[");
        char temp2[20] = {0};
        int i;
        for (i = 0; i < a->count; i++) {
            sprintf(temp2, "%f, ", a->values[i]);
            strcat(strval, temp2);
            // printf("---%s\n", strval);
        }
        // sprintf(temp2, "%f]", a->values[a->count-1]);
        // strcat(strval, temp2);
        strcat(strval, "]");
    }
    file_content_set("lolo.txt", strval);
    return strval;
}

void array_print_(struct array *a, char *name)
{
    size_t count = (!a ? 0 : a->count);
    char *strval = array_strval(a);
    printf("array %s:\n\tcount = %zu\n\tvalues = %s\n", name, count, strval);
    free_safe(strval);
}

void array_print_raw(struct array *a)
{
    char *strval = array_strval(a);
    printf("%s\n", strval);
    free_safe(strval);
}