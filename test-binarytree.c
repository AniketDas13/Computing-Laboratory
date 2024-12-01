#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10

typedef int DATA;

typedef struct tnode
{
    DATA d;
    int left, right, parent;
} TNODE;

typedef struct
{
    int capacity, num_nodes, root;
    TNODE *node_list;
} TREE;

void preorder(TREE tree, int root)
{
    if (root == -1)
    {
        return;
    }

    printf("%d ", tree.node_list[root].d);
    preorder(tree, tree.node_list[root].left);
    preorder(tree, tree.node_list[root].right);
}

void inorder(TREE *tree, int root)
{
    if (root == -1)
    {
        return;
    }

    inorder(tree, tree->node_list[root].left);
    printf("%d ", tree->node_list[root].d);
    inorder(tree, tree->node_list[root].right);
}

void postorder(TREE tree, int root)
{
    if (root == -1)
    {
        return;
    }

    postorder(tree, tree.node_list[root].left);
    postorder(tree, tree.node_list[root].right);
    printf("%d ", tree.node_list[root].d);
}

int init_tree(TREE *t, int capacity)
{
    t->capacity = capacity;
    t->root = -1;
    t->num_nodes = 0;
    t->node_list = (TNODE *)malloc(capacity * sizeof(TNODE));

    if (t->node_list == NULL)
    {
        return -1;
    }

    return 0;
}

void read_tree(TREE *tree)
{
    scanf("%d", &(tree->num_nodes));

    tree->root = 0;
    tree->node_list = (TNODE *)realloc(tree->node_list, tree->num_nodes * sizeof(TNODE));
    tree->node_list[tree->root].parent = -1;

    for (int i = 0; i < tree->num_nodes; i++)
    {
        scanf("%d %d %d", &(tree->node_list[i].d), &(tree->node_list[i].left), &(tree->node_list[i].right));
        if (tree->node_list[i].left != -1)
        {
            tree->node_list[tree->node_list[i].left].parent = i;
        }
        if (tree->node_list[i].right != -1)
        {
            tree->node_list[tree->node_list[i].right].parent = i;
        }
    }
}

int main()
{
    TREE tree;
    if (-1 == init_tree(&tree, CAPACITY))
    {
        return 1;
    }

    read_tree(&tree);

    printf("Preorder traversal: ");
    preorder(tree, tree.root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(&tree, tree.root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(tree, tree.root);
    printf("\n");

    return 0;
}