#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t element_size;
    unsigned int num_allocated, num_used;
    void *array;
    int (*comparator)(void *, int, int);
} HEAP;

void initHeap(HEAP *h, size_t element_size, int (*comparator)(void *, int, int))
{
    h->element_size = element_size;
    h->num_allocated = 10;
    h->num_used = 0;
    h->array = malloc(h->num_allocated * element_size);
    if (h->array == NULL)
    {
        perror("initHeap: out of memory");
        exit(-1);
    }
    h->comparator = comparator;
}

static void swap(HEAP *h, int i, int j)
{
    char *temp = malloc(h->element_size);
    memcpy(temp, (char *)h->array + i * h->element_size, h->element_size);
    memcpy((char *)h->array + i * h->element_size, (char *)h->array + j * h->element_size, h->element_size);
    memcpy((char *)h->array + j * h->element_size, temp, h->element_size);
    free(temp);
}

static void swapUp(HEAP *h, int k)
{
    while (k > 1 && h->comparator(h->array, k / 2, k) < 0)
    {
        swap(h, k, k / 2);
        k /= 2;
    }
}

static void swapDown(HEAP *h, int k)
{
    while (2 * k <= h->num_used)
    {
        int j = 2 * k;
        if (j < h->num_used && h->comparator(h->array, j, j + 1) < 0)
        {
            j++;
        }
        if (h->comparator(h->array, k, j) >= 0)
        {
            break;
        }
        swap(h, k, j);
        k = j;
    }
}

void insert(HEAP *h, void *x)
{
    if (h->num_used + 1 == h->num_allocated)
    {
        h->num_allocated *= 2;
        void *newArray = realloc(h->array, h->num_allocated * h->element_size);
        if (newArray == NULL)
        {
            perror("insert: out of memory");
            exit(-1);
        }
        h->array = newArray;
    }

    h->num_used++;
    memcpy((char *)h->array + h->num_used * h->element_size, x, h->element_size);
    swapUp(h, h->num_used);
}

void *deleteMax(HEAP *h)
{
    if (h->num_used == 0)
    {
        printf("Heap is empty\n");
        return NULL;
    }

    void *max = malloc(h->element_size);
    memcpy(max, (char *)h->array + h->element_size, h->element_size);

    memcpy((char *)h->array + h->element_size, (char *)h->array + h->num_used * h->element_size, h->element_size);
    h->num_used--;
    swapDown(h, 1);
    return max;
}

int int_compare(void *array, int i, int j)
{
    return ((int *)array)[i] - ((int *)array)[j];
}

int main()
{
    HEAP h;
    initHeap(&h, sizeof(int), int_compare);

    insert(&h, 10);
    insert(&h, 5);
    insert(&h, 15);
    insert(&h, 3);
    insert(&h, 8);

    while (h.num_used > 0)
    {
        int max = *(int *)deleteMax(&h);
        printf("%d ", max);
    }

    printf("\n");

    return 0;
}