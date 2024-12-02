#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int value;
    int list_index;
    int next_index;
} HEAP_NODE;

typedef struct
{
    HEAP_NODE *array;
    int size;
    int capacity;
} MIN_HEAP;

void init_min_heap(MIN_HEAP *heap, int capacity)
{
    heap->array = (HEAP_NODE *)malloc(capacity * sizeof(HEAP_NODE));
    heap->size = 0;
    heap->capacity = capacity;
}

void swap(HEAP_NODE *a, HEAP_NODE *b)
{
    HEAP_NODE temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MIN_HEAP *heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->array[left].value < heap->array[smallest].value)
    {
        smallest = left;
    }
    if (right < heap->size && heap->array[right].value < heap->array[smallest].value)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swap(&heap->array[smallest], &heap->array[index]);
        min_heapify(heap, smallest);
    }
}

void insert_heap(MIN_HEAP *heap, HEAP_NODE node)
{
    if (heap->size == heap->capacity)
        return;

    heap->size++;
    int i = heap->size - 1;
    heap->array[i] = node;

    while (i != 0 && heap->array[(i - 1) / 2].value > heap->array[i].value)
    {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HEAP_NODE extract_min(MIN_HEAP *heap)
{
    HEAP_NODE root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);
    return root;
}

void merge_k_sorted_lists(int k, int **lists, int *sizes)
{
    MIN_HEAP heap;
    init_min_heap(&heap, k);

    for (int i = 0; i < k; i++)
    {
        if (sizes[i] > 0)
        {
            HEAP_NODE node = {lists[i][0], i, 1};
            insert_heap(&heap, node);
        }
    }

    printf("Merged list: ");
    while (heap.size > 0)
    {
        HEAP_NODE min_node = extract_min(&heap);
        printf("%d ", min_node.value);

        if (min_node.next_index < sizes[min_node.list_index])
        {
            min_node.value = lists[min_node.list_index][min_node.next_index++];
            insert_heap(&heap, min_node);
        }
    }
    printf("\n");

    free(heap.array);
}

int main()
{
    int k = 4;
    int sizes[] = {3, 2, 5, 4};
    int list1[] = {10, 20, 30};
    int list2[] = {1, 2};
    int list3[] = {5, 15, 25, 30, 35};
    int list4[] = {3, 9, 27, 81};

    int *lists[] = {list1, list2, list3, list4};

    merge_k_sorted_lists(k, lists, sizes);

    return 0;
}