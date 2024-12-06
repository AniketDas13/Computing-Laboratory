#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int init_queue(QUEUE *q, size_t element_size, size_t capacity)
{
    if (element_size <= 0 || capacity <= 0)
        return -1;

    q->element_size = element_size;
    q->capacity = capacity;
    q->num_elements = 0;
    q->front = 0;
    q->rear = 0;
    q->elements = malloc(element_size * capacity);
    if (!q->elements)
        return -1;

    return 0;
}

void free_queue(QUEUE *q)
{
    free(q->elements);
    q->elements = NULL;
    q->num_elements = 0;
    q->capacity = 0;
    q->element_size = 0;
    q->front = 0;
    q->rear = 0;
}

bool is_empty_queue(const QUEUE *q)
{
    return q->num_elements == 0;
}

bool is_full(const QUEUE *q)
{
    return q->num_elements == q->capacity;
}

int enqueue(QUEUE *q, const void *eptr)
{
    if (is_full(q))
        return -1; // Queue is full

    void *dest = (char *)q->elements + (q->rear * q->element_size);
    memcpy(dest, eptr, q->element_size);
    q->rear = (q->rear + 1) % q->capacity;
    q->num_elements++;
    return 0;
}

int dequeue(QUEUE *q, void *eptr)
{
    if (is_empty_queue(q))
        return -1; // Queue is empty

    if (eptr)
    {
        void *src = (char *)q->elements + (q->front * q->element_size);
        memcpy(eptr, src, q->element_size);
    }
    q->front = (q->front + 1) % q->capacity;
    q->num_elements--;
    return 0;
}
