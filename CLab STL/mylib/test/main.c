#include <stdio.h>
#include "../include/stack.h"
// #include "../include/queue.h"
#include "../include/heap.h"
#include "../include/tree.h"

int compare_int(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    // Return negative if int_a < int_b, 0 if equal, positive if int_a > int_b
    return int_a - int_b;
}

void test_stack()
{
    printf("Testing Stack:\n");
    STACK s;
    init_stack(&s, sizeof(int), 5);

    int a = 10, b = 20, c = 30;
    push(&s, &a);
    push(&s, &b);
    push(&s, &c);

    printf("Stack after pushing 10, 20, 30:\n");
    int top_elem;
    while (!is_empty(&s))
    {
        pop(&s, &top_elem);
        printf("%d ", top_elem);
    }
    printf("\n");
}

// void test_queue() {
//     printf("Testing Queue:\n");
//     QUEUE q;
//     init_queue(&q, sizeof(char), 5);

//     char x = 'A', y = 'B', z = 'C';
//     enqueue(&q, &x);
//     enqueue(&q, &y);
//     enqueue(&q, &z);

//     printf("Queue after enqueuing A, B, C:\n");
//     char front_elem;
//     while (!is_queue_empty(&q)) {
//         dequeue(&q, &front_elem);
//         printf("%c ", front_elem);
//     }
//     printf("\n\n");
//     free_queue(&q);
// }

void test_heap()
{
    printf("Testing Heap:\n");
    GENERIC_HEAP h;

    int elements[] = {10, 5, 30, 20, 15};
    size_t n = sizeof(elements) / sizeof(elements[0]);
    initHeap(&h, sizeof(int), n, (int (*)(const void *, const void *))compare_int);
    for (int i = 0; i < n; i++)
    {
        insert(&h, &elements[i]);
        printf("inserted %d\n",elements[i]);
    }

    printf("Heap after inserting 10, 5, 30, 20, 15:\n");
    int min_elem;
    while (h.num_used > 0)
    {
        deleteMin(&h, &min_elem);
        printf("%d ", min_elem);
    }
    printf("\n");
}

// Print function for integers
void print_int(const void *data)
{
    printf("%d ", *(int *)data);
}

// Free function for integers
void free(void *data)
{
    free(data);
}

void test_bst()
{
    printf("Testing Binary Search Tree:\n");
    BST t;
    init_tree(&t, (int (*)(const void *, const void *))compare_int, print_int, free);

    int elements[] = {15, 10, 20, 8, 12, 17, 25};
    for (int i = 0; i < 7; i++)
    {
        insert_node(&t, &elements[i]);
    }

    printf("BST in-order traversal (should be sorted):\n");
    print_tree(&t);

    printf("\n");
}

int main()
{
    
    // test_bst();
    // test_stack();
    test_heap();

    return 0;
}
// test_queue();
// test_heap();
// rm -rf obj/*.o lib/*.a test_program
// bash build.sh
// gcc -o main test/main.c -Iinclude -Llib -lmylib
