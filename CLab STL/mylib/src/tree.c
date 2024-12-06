#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Initialize the BST
void init_tree(BST *tree, int (*compare)(const void *, const void *),
               void (*print)(const void *), void (*free_data)(void *))
{
    tree->root = NULL;
    tree->compare = compare;
    tree->print = print;
    tree->free_data = free_data;
}

// Helper function to create a new node
TNODE *create_node(void *data, size_t data_size)
{
    TNODE *new_node = (TNODE *)malloc(sizeof(TNODE));
    new_node->data = malloc(data_size);
    if (!new_node || !new_node->data)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->data, data, data_size);
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

// Insert a new node into the BST
void insert_node(BST *tree, void *data)
{
    TNODE *new_node = create_node(data, sizeof(data));

    if (!tree->root)
    {
        tree->root = new_node;
        return;
    }

    TNODE *current = tree->root, *parent = NULL;
    while (current)
    {
        parent = current;
        if (tree->compare(data, current->data) < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (tree->compare(data, parent->data) < 0)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }
    new_node->parent = parent;
}

// Helper to recursively print the tree (inorder traversal)
void print_tree_recursive(const TNODE *node, void (*print)(const void *))
{
    if (!node)
        return;
    print_tree_recursive(node->left, print);
    print(node->data);
    print_tree_recursive(node->right, print);
}

// Print the tree
void print_tree(const BST *tree)
{
    print_tree_recursive(tree->root, tree->print);
    printf("\n");
}

// Helper to recursively free nodes
void free_nodes(TNODE *node, void (*free_data)(void *))
{
    if (!node)
        return;
    free_nodes(node->left, free_data);
    free_nodes(node->right, free_data);
    free_data(node->data);
    free(node);
}

// Free the entire tree
void free_tree(BST *tree)
{
    free_nodes(tree->root, tree->free_data);
}
