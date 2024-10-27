#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10000

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

int init_tree(TREE *t, int capacity)
{
    t->capacity = capacity;
    t->root = -1;
    t->num_nodes = 0;
    t->node_list = (TNODE *)malloc(capacity * sizeof(TNODE));

    if (t->node_list == NULL)
    {
        return -1; // Memory allocation failed
    }

    return 0;
}

int insert(TREE *tree, DATA data)
{
    if (tree->num_nodes == tree->capacity)
    {
        printf("Tree is full.\n");
        return -1;
    }

    TNODE *node = &tree->node_list[tree->num_nodes];
    node->d = data;
    node->left = node->right = node->parent = -1;

    if (tree->root == -1)
    {
        tree->root = tree->num_nodes;
    }
    else
    {
        int current = tree->root;
        while (1)
        {
            if (data < tree->node_list[current].d)
            {
                if (tree->node_list[current].left == -1)
                {
                    tree->node_list[current].left = tree->num_nodes;
                    node->parent = current;
                    break;
                }
                else
                {
                    current = tree->node_list[current].left;
                }
            }
            else
            {
                if (tree->node_list[current].right == -1)
                {
                    tree->node_list[current].right = tree->num_nodes;
                    node->parent = current;
                    break;
                }
                else
                {
                    current = tree->node_list[current].right;
                }
            }
        }
    }

    tree->num_nodes++;
    return 0;
}

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

void inorder(TREE tree, int root)
{
    if (root == -1)
    {
        return;
    }

    inorder(tree, tree.node_list[root].left);
    printf("%d ", tree.node_list[root].d);
    inorder(tree, tree.node_list[root].right);
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

int main()
{
    TREE tree;
    init_tree(&tree, CAPACITY);

    insert(&tree, 50);
    insert(&tree, 30);
    insert(&tree, 70);
    insert(&tree, 20);
    insert(&tree, 40);
    insert(&tree, 60);
    insert(&tree, 80);

    printf("Preorder traversal: ");
    preorder(tree, tree.root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(tree, tree.root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(tree, tree.root);
    printf("\n");

    return 0;
}