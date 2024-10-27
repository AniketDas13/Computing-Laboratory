#include <stdio.h>
#include <stdlib.h>

typedef struct tnode
{
    int data;
    int left, right, parent;
} TNODE;

typedef struct
{
    int capacity, num_nodes, root;
    TNODE *node_list;
} TREE;

int newNode(TREE *tree, int data)
{
    if (tree->num_nodes == tree->capacity)
    {
        // Handle capacity overflow, e.g., reallocate or error handling
        return -1;
    }

    tree->node_list[tree->num_nodes].data = data;
    tree->node_list[tree->num_nodes].left = -1;
    tree->node_list[tree->num_nodes].right = -1;
    tree->node_list[tree->num_nodes].parent = -1;
    return tree->num_nodes++;
}

int buildTreeUtil(TREE *tree, int inorder[], int preorder[], int inStart, int inEnd, int preStart, int preEnd)
{
    if (inStart > inEnd)
        return -1;

    int rootIndex = newNode(tree, preorder[preStart]);

    if (inStart == inEnd)
        return rootIndex;

    int inIndex = 0;
    for (int i = inStart; i <= inEnd; i++)
    {
        if (inorder[i] == preorder[preStart])
        {
            inIndex = i;
            break;
        }
    }

    int leftIndex = buildTreeUtil(tree, inorder, preorder, inStart, inIndex - 1, preStart + 1, preStart + inIndex - inStart);
    int rightIndex = buildTreeUtil(tree, inorder, preorder, inIndex + 1, inEnd, preStart + inIndex - inStart + 1, preEnd);

    if (leftIndex != -1)
    {
        tree->node_list[rootIndex].left = leftIndex;
        tree->node_list[leftIndex].parent = rootIndex;
    }

    if (rightIndex != -1)
    {
        tree->node_list[rootIndex].right = rightIndex;
        tree->node_list[rightIndex].parent = rootIndex;
    }

    return rootIndex;
}

void buildTree(TREE *tree, int inorder[], int preorder[], int n)
{
    tree->root = buildTreeUtil(tree, inorder, preorder, 0, n - 1, 0, n - 1);
}

// Function to print the tree in inorder traversal
void printInorder(TREE *tree, int index)
{
    if (index == -1)
        return;

    printInorder(tree, tree->node_list[index].left);
    printf("%d ", tree->node_list[index].data);
    printInorder(tree, tree->node_list[index].right);
}

int main()
{
    int inorder[] = {3, 9, 20, 15, 7};
    int preorder[] = {9, 3, 15, 20, 7};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    // Create a TREE object and initialize it
    TREE tree;
    tree.capacity = n;
    tree.num_nodes = 0;
    tree.node_list = (TNODE *)malloc(n * sizeof(TNODE));

    buildTree(&tree, inorder, preorder, n);

    printf("Inorder traversal of the constructed tree: ");
    printInorder(&tree, tree.root);

    return 0;
}