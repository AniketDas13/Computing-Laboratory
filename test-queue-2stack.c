#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int capacity, top;
    int *contents;
} STACK;

// Function to initialize a stack
void initializeStack(STACK *stack, unsigned int capacity)
{
    stack->capacity = capacity;
    stack->top = -1;
    stack->contents = (int *)malloc(capacity * sizeof(int));
}

// Function to check if a stack is empty
int isEmptyStack(STACK *stack)
{
    return stack->top == -1;
}

// Function to check if a stack is full
int isFullStack(STACK *stack)
{
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto a stack
void push(STACK *stack, int data)
{
    if (isFullStack(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->contents[++stack->top] = data;
}

// Function to pop an element from a stack
int pop(STACK *stack)
{
    if (isEmptyStack(stack))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->contents[stack->top--];
}

// Function to enqueue an element to the queue
void enqueue(STACK *s1, STACK *s2, int data)
{
    push(s1, data);
}

// Function to dequeue an element from the queue
int dequeue(STACK *s1, STACK *s2)
{
    if (isEmptyStack(s2))
    {
        while (!isEmptyStack(s1))
        {
            push(s2, pop(s1));
        }
    }
    return pop(s2);
}

// Function to print the stack
void print_stack(STACK *stack)
{
    if (isEmptyStack(stack))
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack: ");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->contents[i]);
    }
    printf("\n");
}

int main()
{
    STACK s1, s2;
    initializeStack(&s1, 100);
    initializeStack(&s2, 100);

    enqueue(&s1, &s2, 10);
    print_stack(&s1);
    print_stack(&s2);

    enqueue(&s1, &s2, 20);
    print_stack(&s1);
    print_stack(&s2);

    printf("Dequeued element: %d\n", dequeue(&s1, &s2));
    print_stack(&s1);
    print_stack(&s2);

    enqueue(&s1, &s2, 30);
    print_stack(&s1);
    print_stack(&s2);

    enqueue(&s1, &s2, 40);
    print_stack(&s1);
    print_stack(&s2);

    enqueue(&s1, &s2, 50);
    print_stack(&s1);
    print_stack(&s2);

    printf("Dequeued element: %d\n", dequeue(&s1, &s2));
    print_stack(&s1);
    print_stack(&s2);

    printf("Dequeued element: %d\n", dequeue(&s1, &s2));
    print_stack(&s1);
    print_stack(&s2);

    printf("Dequeued element: %d\n", dequeue(&s1, &s2));
    print_stack(&s1);
    print_stack(&s2);

    return 0;
}