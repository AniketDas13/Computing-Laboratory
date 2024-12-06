#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void swapElements(void *a, void *b, size_t size)
{
    char *temp = malloc(size);
    if (!temp)
    {
        perror("swapElements: Out of memory");
        exit(-1);
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

static void swapUp(GENERIC_HEAP *h, int k)
{
    while (k > 0 && h->compare((char *)h->array + (k - 1) / 2 * h->element_size,
                               (char *)h->array + k * h->element_size) > 0)
    {
        swapElements((char *)h->array + (k - 1) / 2 * h->element_size,
                     (char *)h->array + k * h->element_size,
                     h->element_size);
        k = (k - 1) / 2;
    }
}

static void swapDown(GENERIC_HEAP *h, int k)
{
    while (2 * k + 1 < h->num_used)
    {
        int j = 2 * k + 1;
        if (j + 1 < h->num_used &&
            h->compare((char *)h->array + j * h->element_size,
                       (char *)h->array + (j + 1) * h->element_size) > 0)
        {
            j++;
        }
        if (h->compare((char *)h->array + k * h->element_size,
                       (char *)h->array + j * h->element_size) <= 0)
        {
            break;
        }
        swapElements((char *)h->array + k * h->element_size,
                     (char *)h->array + j * h->element_size,
                     h->element_size);
        k = j;
    }
}

void initHeap(GENERIC_HEAP *h, size_t element_size, size_t capacity, int (*compare)(const void *, const void *))
{
    h->element_size = element_size;
    h->num_allocated = capacity > 0 ? capacity : 1000;
    h->num_used = 0;
    h->compare = compare;
    h->array = malloc(h->num_allocated * element_size);
    if (!h->array)
    {
        perror("initHeap: Out of memory");
        exit(-1);
    }
}

void freeHeap(GENERIC_HEAP *h)
{
    free(h->array);
    h->array = NULL;
    h->num_allocated = 0;
    h->num_used = 0;
}

void insert(GENERIC_HEAP *h, const void *element)
{
    if (h->num_used == h->num_allocated)
    {
        h->num_allocated *= 2;
        h->array = realloc(h->array, h->num_allocated * h->element_size);
        if (!h->array)
        {
            perror("insert: Out of memory");
            exit(-1);
        }
    }
    memcpy((char *)h->array + h->num_used * h->element_size, element, h->element_size);
    swapUp(h, h->num_used);
    h->num_used++;
}

int deleteMin(GENERIC_HEAP *h, void *out)
{
    if (h->num_used == 0)
    {
        return -1; // Heap underflow
    }
    if (out)
    {
        memcpy(out, h->array, h->element_size);
    }
    memcpy(h->array, (char *)h->array + (h->num_used - 1) * h->element_size, h->element_size);
    h->num_used--;
    swapDown(h, 0);
    return 0;
}

void heapSort(void *array, size_t N, size_t element_size, int (*compare)(const void *, const void *))
{
    GENERIC_HEAP h;
    initHeap(&h, element_size, N, compare);

    for (size_t i = 0; i < N; i++)
    {
        insert(&h, (char *)array + i * element_size);
    }

    for (size_t i = 0; i < N; i++)
    {
        deleteMin(&h, (char *)array + i * element_size);
    }

    freeHeap(&h);
}
