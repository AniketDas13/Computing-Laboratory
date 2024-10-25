#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int capacity, front, rear;
    int *contents;
} QUEUE;

// Function to initialize the queue
void initialize(QUEUE *queue, unsigned int capacity)
{
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->contents = (int *)malloc(capacity * sizeof(int));
}

// Function to check if the queue is empty
int isEmpty(QUEUE *queue)
{
    return queue->front == -1;
}

// Function to check if the queue is full
int isFull(QUEUE *queue)
{
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Function to enqueue an element
void enqueue(QUEUE *queue, int data)
{
    if (isFull(queue))
    {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmpty(queue))
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }
    queue->contents[queue->rear] = data;
    printf("%d enqueued to queue\n", data);
}

// Function to dequeue an element
int dequeue(QUEUE *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue Underflow\n");
        return -1;
    }
    int data = queue->contents[queue->front];
    if (queue->front == queue->rear)
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return data;
}

// Function to peek at the front element
int peek(QUEUE *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->contents[queue->front];
}

// Function to print the queue
void print_queue(QUEUE *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity)
    {
        printf("%d ", queue->contents[i]);
    }
    printf("%d\n", queue->contents[queue->rear]);
}

int main()
{
    QUEUE queue;
    initialize(&queue, 10);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    print_queue(&queue);

    printf("Dequeued element: %d\n", dequeue(&queue));
    print_queue(&queue);

    printf("Front element: %d\n", peek(&queue));

    return 0;
}