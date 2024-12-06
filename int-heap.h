#ifndef _INTHEAP_H_
#define _INTHEAP_H_

#define INIT_HEAP_SIZE 100

typedef struct
{
    unsigned int num_allocated, num_used;
    int *array; /* one-based indexing used (cf. SEDGEWICK AND WAYNE) */
} INT_HEAP;

void initHeap(INT_HEAP *h);
void insert(INT_HEAP *h, int x);
int deleteMax(INT_HEAP *h);
void buildheap(INT_HEAP *h);
void heapsort(int *a, int N);

#endif // _INT_HEAP_H