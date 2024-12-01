#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// gcc -o avl_example main.c stl.a
// Comparison function for integers
int int_comp(const void *a, const void *b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

// Function to print an integer key
void print_int_key(const void *key)
{
    printf("%d", *(int *)key);
}

int main()
{
    TREE tree;
    int capacity = 100; // Maximum number of nodes
    size_t key_size = sizeof(int);

    // Initialize the AVL tree
    if (avl_init(&tree, key_size, capacity, int_comp) != 0)
    {
        fprintf(stderr, "Failed to initialize AVL tree.\n");
        return 1;
    }

    // Insert some keys into the tree
    int keys_to_insert[] = {10, 20, 5, 6, 15, 30, 25, 35};
    for (int i = 0; i < sizeof(keys_to_insert) / sizeof(keys_to_insert[0]); i++)
    {
        if (avl_insert(&tree, &keys_to_insert[i]) != 0)
        {
            fprintf(stderr, "Failed to insert key: %d\n", keys_to_insert[i]);
        }
    }

    // Search for a key
    int key_to_search = 15;
    int result = avl_search(&tree, &key_to_search);
    if (result != -1)
    {
        printf("Key %d found at index %d.\n", key_to_search, result);
    }
    else
    {
        printf("Key %d not found.\n", key_to_search);
    }

    // Delete a key
    int key_to_delete = 20;
    if (avl_delete(&tree, &key_to_delete) == 0)
    {
        printf("Key %d deleted successfully.\n", key_to_delete);
    }
    else
    {
        printf("Failed to delete key %d.\n", key_to_delete);
    }

    // Print the tree
    printf("Tree structure (rotated):\n");
    avl_print_rotated(&tree, print_int_key, 80);

    // Retrieve all keys
    int *keys = malloc(capacity * key_size);
    if (avl_keys(&tree, keys) == 0)
    {
        printf("Keys in AVL tree: ");
        for (size_t i = 0; i < tree.size; i++)
        {
            printf("%d ", keys[i]);
        }
        printf("\n");
    }
    free(keys);

    return 0;
}