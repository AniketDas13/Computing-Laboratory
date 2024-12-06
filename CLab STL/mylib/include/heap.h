#ifndef _GHEAP_
#define _GHEAP_

#include <stddef.h>  // For size_t
#include <stdbool.h> // For bool

typedef struct {
    void *array;
    size_t element_size, num_allocated, num_used;
    int (*compare)(const void *, const void *); // Comparison function
} GENERIC_HEAP;

void initHeap(GENERIC_HEAP *h, size_t element_size, size_t capacity, int (*compare)(const void *, const void *));
void freeHeap(GENERIC_HEAP *h);
void insert(GENERIC_HEAP *h, const void *element);
int deleteMin(GENERIC_HEAP *h, void *out);
// void buildHeap(GENERIC_HEAP *h);
void heapSort(void *array, size_t N, size_t element_size, int (*compare)(const void *, const void *));

#endif // _GHEAP_
