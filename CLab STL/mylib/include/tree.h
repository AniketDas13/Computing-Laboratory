#ifndef GENERIC_BST_H
#define GENERIC_BST_H

typedef struct tnode {
    void *data;              // Generic data
    struct tnode *left, *right, *parent;
} TNODE;

typedef struct {
    TNODE *root;
    int (*compare)(const void *, const void *); // Comparison function
    void (*print)(const void *);               // Print function
    void (*free_data)(void *);                 // Free function
} BST;

// Function prototypes
void init_tree(BST *tree, int (*compare)(const void *, const void *), 
               void (*print)(const void *), void (*free_data)(void *));
void insert_node(BST *tree, void *data);
void print_tree(const BST *tree);
void free_tree(BST *tree);

#endif // GENERIC_BST_H
