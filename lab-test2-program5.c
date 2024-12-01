#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 1000

typedef struct tnode
{
    int left, right, parent;
} TNODE;

TNODE tree[MAX_NODES];
bool isChild[MAX_NODES]; // To mark nodes as children
int root[MAX_NODES];     // To store roots of all trees
int numRoots = 0;        // Number of trees in the forest

// Preorder traversal
void preorder(int node, int *countFewerThanTwo, int *result, int *index)
{
    if (node == -1)
        return;

    // Add the current node to the preorder result
    result[(*index)++] = node;

    // Check the number of children for the current node
    int childrenCount = 0;
    if (tree[node].left != -1)
        childrenCount++;
    if (tree[node].right != -1)
        childrenCount++;
    if (childrenCount < 2)
        (*countFewerThanTwo)++;

    // Traverse the left and right children
    preorder(tree[node].left, countFewerThanTwo, result, index);
    preorder(tree[node].right, countFewerThanTwo, result, index);
}

int main()
{
    int N;
    scanf("%d", &N);

    // Initialize the tree and isChild arrays
    for (int i = 0; i < N; i++)
    {
        tree[i].parent = -1;
        isChild[i] = false;
    }

    // Read the input and populate the tree
    for (int i = 0; i < N; i++)
    {
        int left, right;
        scanf("%d %d", &left, &right);

        tree[i].left = left;
        tree[i].right = right;

        if (left != -1)
        {
            tree[left].parent = i;
            isChild[left] = true;
        }
        if (right != -1)
        {
            tree[right].parent = i;
            isChild[right] = true;
        }
    }

    // Find the root nodes
    for (int i = 0; i < N; i++)
    {
        if (!isChild[i])
        {
            root[numRoots++] = i;
        }
    }

    // Process each tree in the forest
    for (int i = 0; i < numRoots; i++)
    {
        int currentRoot = root[i];
        int countFewerThanTwo = 0;
        int result[MAX_NODES];
        int index = 0;

        // Perform preorder traversal
        preorder(currentRoot, &countFewerThanTwo, result, &index);

        // Output the result for this tree
        for (int j = 0; j < index; j++)
        {
            printf("%d ", result[j]);
        }

        printf("%d\n", countFewerThanTwo);
    }

    return 0;
}