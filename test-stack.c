#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int capacity, top;
    int *contents;
} STACK;

// Function to initialize the stack
void initialize(STACK *stack, unsigned int capacity)
{
    stack->capacity = capacity;
    stack->top = -1;
    stack->contents = (int *)malloc(capacity * sizeof(int));
}

// STACK init_stack()
// {
//     STACK s;

//     s.capacity = INITIAL_STACK_SIZE;
//     s.top = 0;
//     if (NULL == (s.contents = Malloc(INITIAL_STACK_SIZE, DATA)))
//         ERR_MESG("stack: out of memory\n");

//     return s;
// }

// Function to check if the stack is empty
int isEmpty(STACK *stack)
{
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(STACK *stack)
{
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto the stack
void push(STACK *stack, int data)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->contents[++stack->top] = data;
    printf("%d pushed to stack\n", data);
}

// Function to pop an element from the stack
int pop(STACK *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->contents[stack->top--];
}

// Function to peek at the top element
int peek(STACK *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->contents[stack->top];
}

// Function to print the stack
void print_stack(STACK *stack)
{
    if (isEmpty(stack))
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
    STACK stack;
    initialize(&stack, 100);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    print_stack(&stack);

    printf("Popped element from stack: %d\n", pop(&stack));
    print_stack(&stack);

    printf("Top element is: %d\n", peek(&stack));

    return 0;
}

// int main()
// {
//     STACK stack;
//     initialize(&stack, 5);
//     int choice, data;

//     while (1)
//     {
//         printf("\nMenu:\n");
//         printf("1. Push\n");
//         printf("2. Pop\n");
//         printf("3. Peek\n");
//         printf("4. Print Stack\n");
//         printf("5. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);

//         switch (choice)
//         {
//         case 1:
//             printf("Enter data to push: ");
//             scanf("%d", &data);
//             push(&stack, data);
//             break;
//         case 2:
//             data = pop(&stack);
//             if (data != -1)
//             {
//                 printf("Popped element: %d\n", data);
//             }
//             break;
//         case 3:
//             data = peek(&stack);
//             if (data != -1)
//             {
//                 printf("Top element: %d\n", data);
//             }
//             break;
//         case 4:
//             print_stack(&stack);
//             break;
//         case 5:
//             exit(0);
//         default:
//             printf("Invalid choice\n");
//         }
//     }

//     return 0;
// }