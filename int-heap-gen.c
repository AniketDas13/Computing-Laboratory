#include "common.h"
#include "int-heap.h"

/*---------------------------------------------------------------------------
 * AUXILIARY FUNCTIONS
 *---------------------------------------------------------------------------*/
static void swapUp(INT_HEAP *h, int k)
{
    int tmp;
    while (k > 1 && (h->array[k / 2] < h->array[k]))
    {
        tmp = h->array[k / 2], h->array[k / 2] = h->array[k], h->array[k] = tmp;
        k = k / 2;
    }
    return;
}

static void swapDown(INT_HEAP *h, int k)
{
    int tmp;
    while (2 * k <= h->num_used)
    {
        int j = 2 * k;
        /* choose child with larger key */
        if (j < h->num_used && (h->array[j] < h->array[j + 1]))
            j++;
        if (h->array[k] >= h->array[j])
            break;
        tmp = h->array[k], h->array[k] = h->array[j], h->array[j] = tmp;
        k = j;
    }
    return;
}

/*---------------------------------------------------------------------------
 * API FUNCTIONS
 *---------------------------------------------------------------------------*/

void initHeap(INT_HEAP *h)
{
    h->num_allocated = INIT_HEAP_SIZE;
    h->num_used = 0;
    if (NULL == (h->array = malloc(h->num_allocated * sizeof(int))))
    {
        perror("initHeap: out of memory");
        exit(-1);
    }
    return;
}

void insert(INT_HEAP *h, int x)
{
    /* First, make sure there's space for another element */
    if (h->num_used + 1 == h->num_allocated)
    {
        h->num_allocated *= 2;
        if (NULL == (h->array = realloc(h->array, h->num_allocated * sizeof(int))))
        {
            perror("insert: out of memory");
            exit(-1);
        }
    }
    /* Insert element at end */
    h->num_used++;
    h->array[h->num_used] = x;

    /* Restore heap property */
    swapUp(h, h->num_used);
    return;
}

int deleteMax(INT_HEAP *h)
{
    int max;
    /* Max is at the root (index 1) */
    max = h->array[1];
    /* Copy last element to root */
    h->array[1] = h->array[h->num_used];
    h->num_used--;
    /* Restore heap property */
    swapDown(h, 1);
    return max;
}

void buildheap(INT_HEAP *h)
{
    int k;

    for (k = h->num_used / 2; k >= 1; k--)
        swapDown(h, k);
    return;
}

void heapsort(int *a, int N)
{
    int tmp;
    INT_HEAP h;

    h.num_allocated = h.num_used = N;
    h.array = a;
    /* Make heap out of array */
    buildheap(&h);
    /* Sort by successive deleteMax */
    while (h.num_used > 1)
    {
        tmp = h.array[1],
        h.array[1] = h.array[h.num_used],
        h.array[h.num_used] = tmp; // move max to end
        h.num_used--;
        swapDown(&h, 1);
    }

    return;
}
