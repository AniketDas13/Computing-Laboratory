#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tnode
{
    int data;
    int left, right, parent;
} TNODE;

typedef struct
{
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    TNODE *nodelist;
} TREE;

int newNode(TREE *tree, int data)
{
    if (tree->num_nodes == tree->max_nodes)
    {
        // Handle capacity overflow, e.g., reallocate or error handling
        return -1;
    }

    tree->nodelist[tree->num_nodes].data = data;
    tree->nodelist[tree->num_nodes].left = -1;
    tree->nodelist[tree->num_nodes].right = -1;
    tree->nodelist[tree->num_nodes].parent = -1;
    return tree->num_nodes++;
}

int insertNode(TREE *tree, int data)
{
    int index = newNode(tree, data);
    if (index == -1)
    {
        // Handle capacity overflow
        return -1;
    }

    // If the tree is empty, make the new node the root
    if (tree->root == -1)
    {
        tree->root = index;
        return index;
    }

    // Find the appropriate position for the new node
    int current = tree->root;
    while (1)
    {
        if (data < tree->nodelist[current].data)
        {
            if (tree->nodelist[current].left == -1)
            {
                tree->nodelist[current].left = index;
                tree->nodelist[index].parent = current;
                break;
            }
            else
            {
                current = tree->nodelist[current].left;
            }
        }
        else
        {
            if (tree->nodelist[current].right == -1)
            {
                tree->nodelist[current].right = index;
                tree->nodelist[index].parent = current;
                break;
            }
            else
            {
                current = tree->nodelist[current].right;
            }
        }
    }

    return index;
}

int height(TREE *tree, int index)
{
    if (index == -1)
    {
        return 0;
    }

    int leftHeight = height(tree, tree->nodelist[index].left);
    int rightHeight = height(tree, tree->nodelist[index].right);

    return 1 + fmax(leftHeight, rightHeight);
}

int main()
{
    TREE tree;
    tree.max_nodes = 100;
    tree.num_nodes = 0;
    tree.root = -1;
    tree.free_list = -1;
    tree.nodelist = (TNODE *)malloc(tree.max_nodes * sizeof(TNODE));

    // Insert nodes into the tree
    insertNode(&tree, 10);
    insertNode(&tree, 20);
    insertNode(&tree, 30);
    insertNode(&tree, 40);
    insertNode(&tree, 50);
    insertNode(&tree, 25);

    int treeHeight = height(&tree, tree.root);
    printf("Height of the tree: %d\n", treeHeight);

    return 0;
}