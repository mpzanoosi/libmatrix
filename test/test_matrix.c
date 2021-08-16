#include "array.h"
#include "set.h"

double f1(int dim, double *x)
{
    int i;
    double sum;
    for (i = 0; i < dim; i++) {
        sum = sum + x[i];
    }
    return sum;
}

void test_set()
{
    // int dim_count = 2;
    // struct array *r1 = array_init_by_range(1, 5, 1); // range 1
    // struct array *r2 = array_init_by_range(-1, 0, .5); // range 2
    
    // struct set *s1 = set_init_2d(r1, r2); // s1 = {(x,y) | x \in r1, y \in r2}
    // // set_print(s1);

    // struct matrix *y1;
    // // func_exec(y1, &f1, s1); // y1 = f1(s1); y1 -> matrix, f1 -> functionality
    
    // set_destroy(s1);
    // array_destroy(r1);
    // array_destroy(r2);
}

void test_array()
{
    struct array *a1 = array_init_empty(3);
    array_print_raw(a1);
    array_destroy(a1);
}

int main()
{
    test_array();
    // test_set();
    return 0;
}
