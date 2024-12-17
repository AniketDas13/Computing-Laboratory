#include "common.h"
#include "stack.h"
#include "stack.c"

#define MAX_OPS 100

int main(int ac, char *av[])
{
    int i, x;
    STACK s;

    s = init_stack();

    srand((int)time(NULL));
    for (i = 0; i < MAX_OPS; i++)
    {
        if (rand() % 2)
        {
            x = rand() % MAX_OPS + 1;
            printf("Pushing %d\n", x);
            if (-1 == push(&s, &x))
                fprintf(stderr, "Overflow\n");
            print_stack(&s);
        }
        else
        {
            if (-1 == pop(&s, &x))
                fprintf(stderr, "Underflow\n");
            else
            {
                printf("Popped %d\n", x);
                print_stack(&s);
            }
        }
    }

    /* write a delete_stack in stack.c and call it here to prevent a memory leak */
    return 0;
}