#include <stdio.h>
#include <stdlib.h>

void min_heapify(int *heap, int size, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index)
    {
        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        min_heapify(heap, size, smallest);
    }
}

int extract_min(int *heap, int *size)
{
    int root = heap[0];
    heap[0] = heap[--(*size)];
    min_heapify(heap, *size, 0);
    return root;
}

void insert_heap(int *heap, int *size, int value)
{
    heap[(*size)++] = value;
    for (int i = (*size) / 2 - 1; i >= 0; i--)
    {
        min_heapify(heap, *size, i);
    }
}

int min_cost_to_join_ropes(int *ropes, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        min_heapify(ropes, n, i);
    }

    int total_cost = 0;
    while (n > 1)
    {
        int first = extract_min(ropes, &n);
        int second = extract_min(ropes, &n);

        int cost = first + second;
        total_cost += cost;

        insert_heap(ropes, &n, cost);
    }

    return total_cost;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <rope lengths>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *ropes = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        ropes[i] = atoi(argv[i + 1]);
    }

    int cost = min_cost_to_join_ropes(ropes, n);
    printf("Minimum cost to join ropes: %d\n", cost);

    free(ropes);
    return 0;
}