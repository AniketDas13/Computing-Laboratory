#include <stdio.h>
#include <stdlib.h>

#define INIT_HEAP_SIZE 16

typedef struct
{
    unsigned int num_allocated, num_used;
    int *array;
} INT_HEAP;

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

static void swapUp(INT_HEAP *h, int k)
{
    while (k > 1 && h->array[k / 2] < h->array[k])
    {
        int temp = h->array[k / 2];
        h->array[k / 2] = h->array[k];
        h->array[k] = temp;
        k /= 2;
    }
}

static void swapDown(INT_HEAP *h, int k)
{
    while (2 * k <= h->num_used)
    {
        int j = 2 * k;
        if (j < h->num_used && h->array[j] < h->array[j + 1])
        {
            j++;
        }
        if (h->array[k] >= h->array[j])
        {
            break;
        }
        int temp = h->array[k];
        h->array[k] = h->array[j];
        h->array[j] = temp;
        k = j;
    }
}

void insert(INT_HEAP *h, int x)
{
    if (h->num_used + 1 == h->num_allocated)
    {
        h->num_allocated *= 2;
        if (NULL == (h->array = realloc(h->array, h->num_allocated * sizeof(int))))
        {
            perror("insert: out of memory");
            exit(-1);
        }
    }

    h->num_used++;
    h->array[h->num_used] = x;
    swapUp(h, h->num_used);
}

int deleteMax(INT_HEAP *h)
{
    if (h->num_used == 0)
    {
        printf("Heap is empty\n");
        return -1;
    }

    int max = h->array[1];
    h->array[1] = h->array[h->num_used];
    h->num_used--;
    swapDown(h, 1);
    return max;
}

void buildHeap(INT_HEAP *h)
{
    for (int k = h->num_used / 2; k >= 1; k--)
    {
        swapDown(h, k);
    }
}

void heapsort(int *a, int N)
{
    INT_HEAP h;
    h.num_allocated = h.num_used = N;
    h.array = a;
    buildHeap(&h);

    while (h.num_used > 1)
    {
        int temp = h.array[1];
        h.array[1] = h.array[h.num_used];
        h.array[h.num_used] = temp;
        h.num_used--;
        swapDown(&h, 1);
    }
}

int main()
{
    INT_HEAP h;
    initHeap(&h);

    insert(&h, 10);
    insert(&h, 5);
    insert(&h, 15);
    insert(&h, 3);
    insert(&h, 8);

    while (h.num_used > 0)
    {
        printf("%d ", deleteMax(&h));
    }
    printf("\n");

    int arr[] = {-1, 2, 4, 1, 8, 9, 0, 5, 7, 3, 6};
    heapsort(arr, 10);

    for (int i = 1; i < 11; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}