#include "set.h"

struct set *set_init_empty(size_t dim_count, size_t *counts)
{

}

struct set *set_init_by_array_2d(struct array *a1, struct array *a2)
{
    structinit(struct set, new_set);
    new_set->dim_count = 2;
    new_set->values = (struct array **)malloc(new_set->dim_count * sizeof(struct array *));
    new_set->values[0] = structdup(a1);
    new_set->values[1] = structdup(a2);
    new_set->counts = (size_t *)malloc(new_set->dim_count * sizeof(size_t));
    new_set->counts[0] = new_set->values[0]->count;
    new_set->counts[1] = new_set->values[1]->count;
    new_set->counts_all = new_set->counts[0] * new_set->counts[1];
    return new_set;
}

int set_destroy(struct set *s)
{
    if (!s)
        return 0;
    
    if (s->dim_count < 1) {
        free_safe(s);
        return 0;
    }

    int i;
    for (i = 0; i < s->dim_count; i++) {
        array_destroy(s->values[i]);
    }
    free_safe(s->values);
    free_safe(s);
    return 0;
}

void set_print_(struct set *s, char *name)
{
    if (s->dim_count < 1)
        return;

    printf("number set %s (dim_count = %zu)\n", name, s->dim_count);
    int i;
    for (i = 0; i < s->dim_count; i++) {
        printf("\tdimension %d (count = %zu):\n\t\t", i+1, s->values[i]->count);
        array_print_raw(s->values[i]);
    }
}