#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Maximum size of the stacks

// Stack structure definition
typedef struct
{
    int array[MAX_SIZE]; // Array to hold stack elements
    int top;             // Index of the top element
} STACK;

// Queue structure using two stacks
typedef struct
{
    STACK F; // Stack for dequeue operations
    STACK B; // Stack for enqueue operations
} QUEUE;

// Stack Functions

// Initialize an empty stack
STACK SINIT()
{
    STACK s;
    s.top = -1; // Top is -1, indicating an empty stack
    return s;
}

// Check if a stack is empty
int ISEMPTY(STACK *s)
{
    return s->top == -1;
}

// Check if a stack is full
int ISFULL(STACK *s)
{
    return s->top == MAX_SIZE - 1;
}

// Push an integer x onto the stack, returns 1 on success, 0 on overflow
int PUSH(STACK *s, int x)
{
    if (ISFULL(s))
    {
        printf("Error: Stack overflow while pushing %d\n", x);
        return 0;
    }
    s->array[++(s->top)] = x; // Increment top and add element
    return 1;
}

// Pop an integer from the stack, returns -1 if underflow
int POP(STACK *s)
{
    if (ISEMPTY(s))
    {
        printf("Error: Stack underflow\n");
        return -1;
    }
    return s->array[(s->top)--]; // Return top element and decrement top
}

// Get the element at the top of the stack without removing it
int TOP(STACK *s)
{
    if (ISEMPTY(s))
    {
        printf("Error: Stack is empty, no top element\n");
        return -1;
    }
    return s->array[s->top];
}

// Queue Functions

// Initialize an empty queue
QUEUE QINIT()
{
    QUEUE q;
    q.F = SINIT();
    q.B = SINIT();
    return q;
}

// Enqueue operation: Push to the back stack (B)
int ENQUEUE(QUEUE *q, int x)
{
    if (ISFULL(&(q->B)))
    {
        printf("Error: Queue overflow while enqueuing %d\n", x);
        return 0;
    }
    return PUSH(&(q->B), x);
}

// Dequeue operation: Pop from the front stack (F)
int DEQUEUE(QUEUE *q)
{
    // If both F and B are empty, the queue is empty (underflow)
    if (ISEMPTY(&(q->F)) && ISEMPTY(&(q->B)))
    {
        printf("Error: Queue underflow\n");
        return -1;
    }

    // If F is empty but B has elements, transfer B to F in reverse order
    if (ISEMPTY(&(q->F)))
    {
        while (!ISEMPTY(&(q->B)))
        {
            int x = POP(&(q->B));
            PUSH(&(q->F), x);
        }
    }

    // Now F has elements to pop from the front of the queue
    return POP(&(q->F));
}

// Print the queue from front to back
void QPRINT(QUEUE *q)
{
    // Print elements in F (front stack) from top to bottom
    printf("Queue = [ ");
    for (int i = q->F.top; i >= 0; i--)
    {
        printf("%d ", q->F.array[i]);
    }

    // Print elements in B (back stack) from bottom to top
    for (int i = 0; i <= q->B.top; i++)
    {
        printf("%d ", q->B.array[i]);
    }
    printf("]\n");
}

// Main Function to Handle Input and Execute Queue Operations
int main()
{
    QUEUE q = QINIT(); // Initialize an empty queue
    int operation, value;

    printf("Enter operations (0 for enqueue, 1 for dequeue, -1 to end):\n");

    while (1)
    {
        scanf("%d", &operation);

        // End input on -1
        if (operation == -1)
            break;

        if (operation == 0)
        { // Enqueue operation
            scanf("%d", &value);
            if (ENQUEUE(&q, value))
            {
                printf("Enqueued %d\n", value);
            }
        }
        else if (operation == 1)
        { // Dequeue operation
            int dequeued_value = DEQUEUE(&q);
            if (dequeued_value != -1)
            { // Only print if dequeue was successful
                printf("Dequeued %d\n", dequeued_value);
            }
        }
        else
        {
            printf("Invalid operation! Use 0 for enqueue, 1 for dequeue, -1 to end.\n");
        }

        // Print the queue state after each operation
        QPRINT(&q);
    }

    return 0;
}