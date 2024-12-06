#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int init_stack(STACK *s, int element_size, int capacity)
{
    if (element_size <= 0 || capacity <= 0)
        return -1;

    s->element_size = element_size;
    s->max_elements = capacity;
    s->num_elements = 0;
    s->elements = malloc(element_size * capacity);
    if (!s->elements)
        return -1;

    return 0;
}

void free_stack(STACK *s)
{
    free(s->elements);
    s->elements = NULL;
    s->num_elements = 0;
    s->max_elements = 0;
    s->element_size = 0;
}

bool is_empty(const STACK *s)
{
    return s->num_elements == 0;
}

int push(STACK *s, const void *eptr)
{
    if (s->num_elements == s->max_elements)
    {
        size_t new_capacity = s->max_elements * 2;
        void *new_elements = realloc(s->elements, new_capacity * s->element_size);
        if (!new_elements)
            return -1;

        s->elements = new_elements;
        s->max_elements = new_capacity;
    }

    void *dest = (char *)s->elements + (s->num_elements * s->element_size);
    memcpy(dest, eptr, s->element_size);
    s->num_elements++;
    return 0;
}

int pop(STACK *s, void *eptr)
{
    if (is_empty(s))
        return -1;

    s->num_elements--;
    void *src = (char *)s->elements + (s->num_elements * s->element_size);
    if (eptr)
        memcpy(eptr, src, s->element_size);
    return 0;
}
