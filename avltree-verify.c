#include <stdio.h>
#include <stdlib.h>

// Define the structure for a tree node
typedef struct tnode
{
    int data;  // Node's value
    int left;  // Index of left child (-1 if none)
    int right; // Index of right child (-1 if none)
} TNODE;

// Function prototypes
int isBST(TNODE nodes[], int root, int *min, int *max);
int heightAndBalanced(TNODE nodes[], int root, int *isBalanced);

// Main function to validate AVL consistency
int main()
{
    int N;
    scanf("%d", &N);

    TNODE nodes[N];
    for (int i = 0; i < N; i++)
    {
        int left, right;
        scanf("%d %d", &left, &right);

        nodes[i].data = i; // Assume input order determines node indices
        nodes[i].left = left;
        nodes[i].right = right;
    }

    // Determine the root of the tree (assume input is for a single tree)
    int isChild[N];
    for (int i = 0; i < N; i++)
        isChild[i] = 0;

    for (int i = 0; i < N; i++)
    {
        if (nodes[i].left != -1)
            isChild[nodes[i].left] = 1;
        if (nodes[i].right != -1)
            isChild[nodes[i].right] = 1;
    }

    int root = -1;
    for (int i = 0; i < N; i++)
    {
        if (isChild[i] == 0)
        {
            root = i;
            break;
        }
    }

    if (root == -1)
    {
        printf("Invalid tree: No root found.\n");
        return 1;
    }

    // Check if the tree is a BST
    int min = -1, max = -1;
    int isBSTValid = isBST(nodes, root, &min, &max);

    // Check if the tree is balanced
    int isBalanced = 1;
    heightAndBalanced(nodes, root, &isBalanced);

    // Final AVL tree validation
    if (isBSTValid && isBalanced)
    {
        printf("The tree is an AVL tree.\n");
    }
    else
    {
        printf("The tree is NOT an AVL tree.\n");
    }

    return 0;
}

// Function to check if the tree is a BST
int isBST(TNODE nodes[], int root, int *min, int *max)
{
    if (root == -1)
    {
        *min = *max = -1;
        return 1;
    }

    int leftMin, leftMax, rightMin, rightMax;
    if (!isBST(nodes, nodes[root].left, &leftMin, &leftMax))
        return 0;
    if (!isBST(nodes, nodes[root].right, &rightMin, &rightMax))
        return 0;

    if ((leftMax != -1 && nodes[root].data <= leftMax) ||
        (rightMin != -1 && nodes[root].data >= rightMin))
    {
        return 0;
    }

    *min = (leftMin != -1) ? leftMin : nodes[root].data;
    *max = (rightMax != -1) ? rightMax : nodes[root].data;
    return 1;
}

// Function to compute height and check if the tree is balanced
int heightAndBalanced(TNODE nodes[], int root, int *isBalanced)
{
    if (root == -1)
        return 0;

    int leftHeight = heightAndBalanced(nodes, nodes[root].left, isBalanced);
    int rightHeight = heightAndBalanced(nodes, nodes[root].right, isBalanced);

    if (abs(leftHeight - rightHeight) > 1)
        *isBalanced = 0;

    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}