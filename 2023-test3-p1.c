#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 25

typedef struct
{
    char *array;           // Shared array for both stacks
    int top1, top2;        // Top pointers for colliding strategy
    int odd_top, even_top; // Top pointers for odd-even strategy
    int strategy;          // 0 for odd-even, 1 for colliding
} StackCouple;

// Initialize StackCouple with default values
void init(StackCouple *stack, int strategy)
{
    stack->array = (char *)malloc(MAX_SIZE * sizeof(char));
    for (int i = 0; i < MAX_SIZE; i++)
    {
        stack->array[i] = 0; // Initialize each element to 0
    }
    stack->top1 = -1;
    stack->top2 = MAX_SIZE;
    stack->odd_top = -2;
    stack->even_top = -1;
    stack->strategy = strategy;
}

// Display the stacks for debugging
void display(StackCouple *stack)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%c", stack->array[i] ? stack->array[i] : '_');
    }
    printf("\n");
}

// Push function for Stack 1 and Stack 2
void push(StackCouple *stack, int stack_no, char value)
{
    if (stack->strategy == 1)
    { // Colliding Strategy
        if (stack->top1 + 1 == stack->top2)
        {
            printf("Error: Overflow in stack.\n");
            return;
        }
        if (stack_no == 1)
        {
            stack->array[++stack->top1] = value;
        }
        else
        {
            stack->array[--stack->top2] = value;
        }
    }
    else
    { // Odd-Even Strategy
        if (stack->odd_top + 2 >= MAX_SIZE || stack->even_top + 2 >= MAX_SIZE)
        {
            printf("Error: Overflow in stack.\n");
            return;
        }
        if (stack_no == 1)
        {
            stack->array[stack->odd_top += 2] = value;
        }
        else
        {
            stack->array[stack->even_top += 2] = value;
        }
    }

    display(stack);
}

// Pop function for Stack 1 and Stack 2
void pop(StackCouple *stack, int stack_no)
{
    if (stack->strategy == 1)
    { // Colliding Strategy
        if (stack_no == 1)
        {
            if (stack->top1 == -1)
            {
                printf("Error: Underflow in stack.\n");
                return;
            }
            stack->array[stack->top1--] = 0; // Set popped element to 0
        }
        else
        {
            if (stack->top2 == MAX_SIZE)
            {
                printf("Error: Underflow in stack.\n");
                return;
            }
            stack->array[stack->top2++] = 0; // Set popped element to 0
        }
    }
    else
    { // Odd-Even Strategy
        if (stack_no == 1)
        {
            if (stack->odd_top == -2)
            {
                printf("Error: Underflow in stack.\n");
                return;
            }
            stack->array[stack->odd_top] = 0; // Set popped element to 0
            stack->odd_top -= 2;
        }
        else
        {
            if (stack->even_top == -1)
            {
                printf("Error: Underflow in stack.\n");
                return;
            }
            stack->array[stack->even_top] = 0; // Set popped element to 0
            stack->even_top -= 2;
        }
    }

    display(stack);
}

int main()
{
    StackCouple stack;
    int strategy;
    scanf("%d", &strategy);
    init(&stack, strategy);

    int op, stack_no;
    char value;
    while (1)
    {
        scanf("%d", &op);
        if (op == -1)
            break;
        scanf("%d", &stack_no);
        if (op == 0)
        { // push
            scanf(" %c", &value);
            push(&stack, stack_no, value);
        }
        else if (op == 1)
        { // pop
            pop(&stack, stack_no);
        }
    }

    return 0;
}