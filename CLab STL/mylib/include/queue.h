#ifndef _GQUEUE_
#define _GQUEUE_

#include <stddef.h>  // For size_t
#include <stdbool.h> // For bool

typedef struct
{
    void *elements;
    size_t element_size, capacity, num_elements, front, rear;
} QUEUE;

int init_queue(QUEUE *q, size_t element_size, size_t capacity);
void free_queue(QUEUE *q);
bool is_empty_queue(const QUEUE *q);
bool is_full(const QUEUE *q);
int enqueue(QUEUE *q, const void *eptr);
int dequeue(QUEUE *q, void *eptr);

#endif // _GQUEUE_
