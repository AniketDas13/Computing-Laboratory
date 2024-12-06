#ifndef GENERIC_AVL_TREE_H
#define GENERIC_AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode
{
    void *data; // Pointer to data
    int left, right;
    int parent;
    int height;
} TNODE;

typedef struct
{
    int capacity, num_nodes, root;
    TNODE *nodelist;
    size_t data_size;
    int (*compare)(const void *, const void *); // Comparison function
    void (*print)(const void *);                // Print function
} TREE;

// Function prototypes
void init_tree(TREE *T, int capacity, size_t data_size, int (*compare)(const void *, const void *), void (*print)(const void *));
int insert_node(TREE *T, int root, void *data);
int search(TREE *T, int root, void *data);
void preorder(TREE *T, int root);
void inorder(TREE *T, int root);
void postorder(TREE *T, int root);
void free_tree(TREE *T);

#endif // GENERIC_AVL_TREE_H
