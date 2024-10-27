#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *buildTree(int inorder[], int postorder[], int inStart, int inEnd, int postStart, int postEnd)
{
    if (inStart > inEnd)
        return NULL;

    /* Pick current node */
    int curr = postorder[postEnd];

    /* Find current node in inorder traversal */
    int inIndex = 0;
    for (int i = inStart; i <= inEnd; i++)
    {
        if (inorder[i] == curr)
        {
            inIndex = i;
            break;
        }
    }

    /* Build left subtree */
    struct Node *root = (struct Node *)malloc(sizeof(struct Node));
    root->data = curr;
    root->left = buildTree(inorder, postorder, inStart, inIndex - 1, postStart, postStart + inIndex - inStart - 1);
    root->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postStart + inIndex - inStart, postEnd - 1);

    return root;
}

void printInorder(struct Node *node)
{
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

int main()
{
    int inorder[] = {4, 2, 5, 1, 3, 6};
    int postorder[] = {4, 5, 2, 6, 3, 1};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    struct Node *root = buildTree(inorder, postorder, 0, n - 1, 0, n - 1);

    printf("Inorder traversal of the constructed tree: ");
    printInorder(root);

    return 0;
}