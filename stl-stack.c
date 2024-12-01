#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// gcc -o stack_example main.c stl.a
// Function to print an integer key
void print_int_key(const void *key)
{
    printf("%d", *(int *)key);
}

int main()
{
    STACK stack;
    size_t key_size = sizeof(int);
    size_t capacity = 100; // Maximum number of elements in the stack

    // Initialize the stack
    if (stack_init(&stack, key_size, capacity) != 0)
    {
        fprintf(stderr, "Failed to initialize stack.\n");
        return 1;
    }

    // Push some keys onto the stack
    int keys_to_push[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < sizeof(keys_to_push) / sizeof(keys_to_push[0]); i++)
    {
        if (stack_push(&stack, &keys_to_push[i]) != 0)
        {
            fprintf(stderr, "Failed to push key: %d\n", keys_to_push[i]);
        }
    }

    // Print the stack
    printf("Stack after pushes:\n");
    stack_print(&stack, print_int_key);

    // Peek the top of the stack
    int top_key;
    if (stack_top(&stack, &top_key) == 0)
    {
        printf("\nTop of the stack: %d\n", top_key);
    }
    else
    {
        fprintf(stderr, "Failed to get the top of the stack.\n");
    }

    // Pop keys from the stack
    printf("\nPopping keys from the stack:\n");
    while (stack.size > 0)
    {
        int popped_key;
        if (stack_pop(&stack, &popped_key) == 0)
        {
            printf("Popped key: %d\n", popped_key);
        }
        else
        {
            fprintf(stderr, "Failed to pop key.\n");
        }
    }

    // Print the stack after popping
    printf("\nStack after popping all keys:\n");
    stack_print(&stack, print_int_key);

    return 0;
}