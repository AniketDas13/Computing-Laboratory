#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define HEIGHT(T, nodeindex) (((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height)
#define FAILURE -1

typedef int DATA;

typedef struct node
{
    DATA data;
    int left, right, parent, height;
} AVL_NODE;

typedef struct
{
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    AVL_NODE *nodelist;
} TREE;

/* Initialize the tree */
int init_tree(TREE *tree)
{
    tree->num_nodes = 0;
    tree->max_nodes = 10;
    tree->root = -1;
    tree->free_list = -1;
    tree->nodelist = malloc(tree->max_nodes * sizeof(AVL_NODE));
    if (!tree->nodelist)
        return FAILURE;

    // Initialize free list
    for (int i = 0; i < tree->max_nodes - 1; i++)
    {
        tree->nodelist[i].parent = i + 1; // Chain unused nodes
    }
    tree->nodelist[tree->max_nodes - 1].parent = -1; // End of free list
    tree->free_list = 0;

    return 0;
}

/* Find the successor of a node */
int find_successor(TREE *tree, int node)
{
    int child = tree->nodelist[node].right;
    if (child == -1)
        return -1;
    while (tree->nodelist[child].left != -1)
    {
        child = tree->nodelist[child].left;
    }
    return child;
}

/* Grow the tree when capacity is exhausted */
int grow_tree(TREE *tree)
{
    int old_max = tree->max_nodes;
    int new_max = old_max * 2;
    AVL_NODE *new_list = realloc(tree->nodelist, new_max * sizeof(AVL_NODE));
    if (!new_list)
        return FAILURE;

    tree->nodelist = new_list;
    tree->max_nodes = new_max;

    for (int i = old_max; i < new_max - 1; i++)
    {
        tree->nodelist[i].parent = i + 1;
    }
    tree->nodelist[new_max - 1].parent = -1;
    tree->free_list = old_max;

    return 0;
}

/* Get a new node from the free list */
int get_new_node(TREE *tree)
{
    if (tree->free_list == -1)
    {
        if (grow_tree(tree) == FAILURE)
            return FAILURE;
    }

    int new_node = tree->free_list;
    tree->free_list = tree->nodelist[new_node].parent;
    tree->num_nodes++;
    return new_node;
}

/* Free the entire tree */
void free_tree(TREE *tree)
{
    free(tree->nodelist);
    tree->nodelist = NULL;
    tree->num_nodes = 0;
    tree->max_nodes = 0;
    tree->root = -1;
}

/* Perform an LL rotation */
void rotate_on_insert_LL(TREE *tree, int parent, int *node)
{
    int k2 = *node;
    int k1 = tree->nodelist[k2].left;
    int Y = tree->nodelist[k1].right;

    tree->nodelist[k2].left = Y;
    tree->nodelist[k1].right = k2;

    if (Y != -1)
        tree->nodelist[Y].parent = k2;
    tree->nodelist[k2].parent = k1;
    tree->nodelist[k1].parent = parent;

    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, tree->nodelist[k2].left), HEIGHT(tree, tree->nodelist[k2].right));
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, tree->nodelist[k1].left), HEIGHT(tree, k2));

    *node = k1;
}

/* Perform an RR rotation */
void rotate_on_insert_RR(TREE *tree, int parent, int *node)
{
    int k1 = *node;
    int k2 = tree->nodelist[k1].right;
    int Y = tree->nodelist[k2].left;

    tree->nodelist[k1].right = Y;
    tree->nodelist[k2].left = k1;

    if (Y != -1)
        tree->nodelist[Y].parent = k1;
    tree->nodelist[k1].parent = k2;
    tree->nodelist[k2].parent = parent;

    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, tree->nodelist[k1].left), HEIGHT(tree, tree->nodelist[k1].right));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, tree->nodelist[k2].left), HEIGHT(tree, k1));

    *node = k2;
}

/* Perform an LR rotation */
void rotate_on_insert_LR(TREE *tree, int parent, int *node)
{
    rotate_on_insert_RR(tree, *node, &tree->nodelist[*node].left);
    rotate_on_insert_LL(tree, parent, node);
}

/* Perform an RL rotation */
void rotate_on_insert_RL(TREE *tree, int parent, int *node)
{
    rotate_on_insert_LL(tree, *node, &tree->nodelist[*node].right);
    rotate_on_insert_RR(tree, parent, node);
}

/* Balance the tree */
void balance(TREE *tree, int parent, int *node)
{
    int thisnode = *node;
    int left = tree->nodelist[thisnode].left;
    int right = tree->nodelist[thisnode].right;

    // printf("%d L->%d R->%d H->%d HL->%d HR->%d\n", tree->nodelist[thisnode].data, tree->nodelist[left].data, tree->nodelist[right].data, tree->nodelist[thisnode].height, HEIGHT(tree, left), HEIGHT(tree, right));

    if (HEIGHT(tree, left) - HEIGHT(tree, right) > 1)
    {
        if (HEIGHT(tree, tree->nodelist[left].left) >= HEIGHT(tree, tree->nodelist[left].right))
        {
            rotate_on_insert_LL(tree, parent, node);
        }
        else
        {
            rotate_on_insert_LR(tree, parent, node);
        }
    }
    else if (HEIGHT(tree, right) - HEIGHT(tree, left) > 1)
    {
        if (HEIGHT(tree, tree->nodelist[right].right) >= HEIGHT(tree, tree->nodelist[right].left))
        {
            rotate_on_insert_RR(tree, parent, node);
        }
        else
        {
            rotate_on_insert_RL(tree, parent, node);
        }
    }

    tree->nodelist[thisnode].height = 1 + MAX(HEIGHT(tree, left), HEIGHT(tree, right));
}

/* Insert into the tree */
int insert(TREE *tree, int parent, int *node, DATA data)
{
    if (*node == -1)
    {
        int new_node = get_new_node(tree);
        if (new_node == FAILURE)
            return FAILURE;

        tree->nodelist[new_node].data = data;
        tree->nodelist[new_node].left = -1;
        tree->nodelist[new_node].right = -1;
        tree->nodelist[new_node].parent = parent;
        tree->nodelist[new_node].height = 0;
        *node = new_node;
        return 0;
    }

    if (data < tree->nodelist[*node].data)
    {
        if (insert(tree, *node, &tree->nodelist[*node].left, data) == FAILURE)
            return FAILURE;
    }
    else
    {
        if (insert(tree, *node, &tree->nodelist[*node].right, data) == FAILURE)
            return FAILURE;
    }

    balance(tree, parent, node);

    return 0;
}

/* In-order traversal */
void inorder(TREE *tree, int node)
{
    if (node == -1)
        return;
    inorder(tree, tree->nodelist[node].left);
    printf("%d ", tree->nodelist[node].data);
    inorder(tree, tree->nodelist[node].right);
}

int main()
{
    TREE tree;
    if (init_tree(&tree) == FAILURE)
    {
        printf("Failed to initialize tree.\n");
        return -1;
    }

    insert(&tree, -1, &tree.root, 10);
    insert(&tree, -1, &tree.root, 20);
    insert(&tree, -1, &tree.root, 5);
    insert(&tree, -1, &tree.root, 8);
    insert(&tree, -1, &tree.root, 15);
    insert(&tree, -1, &tree.root, 12);
    insert(&tree, -1, &tree.root, 7);

    printf("In-order Traversal: ");
    inorder(&tree, tree.root);
    printf("\n");

    free_tree(&tree);

    return 0;
}