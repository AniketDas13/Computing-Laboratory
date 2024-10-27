#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *buildTree(int inorder[], int preorder[], int inStart, int inEnd, int preStart, int preEnd)
{
    if (inStart > inEnd)
        return NULL;

    /* Pick current node */
    int curr = preorder[preStart];

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
    root->left = buildTree(inorder, preorder, inStart, inIndex - 1, preStart + 1, preStart + inIndex - inStart);
    root->right = buildTree(inorder, preorder, inIndex + 1, inEnd, preStart + inIndex - inStart + 1, preEnd);

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
    int inorder[] = {3, 9, 20, 15, 7};
    int preorder[] = {9, 3, 15, 20, 7};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    struct Node *root = buildTree(inorder, preorder, 0, n - 1, 0, n - 1);

    printf("Inorder traversal of the constructed tree: ");
    printInorder(root);

    return 0;
}