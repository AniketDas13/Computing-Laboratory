/*
Binary Trees over domain D - as a prerequisite to BST
height of singleton node is 0
write functions to find height, no of nodes and no of leaves in a binary tree
Assuming elements of D can be added meaningfully, weight(T) = sum of values in the nodes
root - level = 0 or 1: state the convention used
depth = length of path from root to that node
** Tree input - as a text file. the tree is given as an array as shown in "Alternative Implementation". **
*/

#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10

typedef int DATA; // do according to the problem
/*
typedef struct tnode // traditional implementation
{
    DATA d;
    // As per the mathematical defn, these 2 should've been tnode variables but compiler can't handle struct tnode inside struct tnode defn, so we use pointers.
    struct tnode *left, *right;
    struct tnode *parent; // optional
} TNODE;
*/

typedef struct tnode
{ // Alternative Implementation. -1 ---> NULL
    DATA d;
    int left, right;
    int parent;
} TNODE;

typedef struct
{
    int capacity, num_nodes, root;
    TNODE *node_list; // an array following the alternative implementation
} TREE;

void preorder(TREE tree, int root)
{ // void preorder(TNODE* T)
    if (tree.node_list == NULL)
        return;
    if (root == -1)
        return;

    printf("(%d %d) ", tree.node_list[root].d, tree.node_list[root].parent);
    preorder(tree, tree.node_list[root].left);
    preorder(tree, tree.node_list[root].right);
}

/* Alternative Implementation*/
int init_tree(TREE *t, int capacity)
{
    /* Creates an empty tree */
    t->capacity = capacity;
    t->root = -1;
    t->num_nodes = 0;
    t->node_list = (TNODE *)malloc(sizeof(TNODE) * capacity);

    if (t->node_list == NULL)
        return -1; // something went wrong

    return 0; // all ok
}

void read_tree(TREE *tree)
{
    TNODE *node;
    scanf("%d", &(tree->num_nodes));

    tree->root = 0; // index of root element in array is 0
    tree->node_list = (TNODE *)realloc(tree->node_list, tree->num_nodes * sizeof(TNODE));
    tree->node_list[tree->root].parent = -1;

    int i;
    for (node = tree->node_list, i = 0; i < tree->num_nodes; i++, node++)
    {
        scanf("%d %d %d", &(node->d), &(node->left), &(node->right));
        if (node->left != -1)
            tree->node_list[node->left].parent = i;
        if (node->right != -1)
            tree->node_list[node->right].parent = i;
    }
}

int main()
{
    /* We are storing the tree as an array of TNODEs */
    TREE tree;

    if (-1 == init_tree(&tree, CAPACITY))
        return 1;
    read_tree(&tree);
    preorder(tree, tree.root);

    return 0;
}