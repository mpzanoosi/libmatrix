#include "array.h"
#include "backtrace.h"

void test_array()
{
    struct array *a1 = array_init_empty(3);
    array_print_raw(a1);
    array_destroy(a1);
}

int main()
{
    // matrix_backtrace_start();
    test_array();
    // test_set();
    return 0;
}
