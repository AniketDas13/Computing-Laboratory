#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node *insert(struct Node *node, int data)
{
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    return node;
}

struct Node *constructBST(int preorder[], int size)
{
    struct Node *root = newNode(preorder[0]);
    for (int i = 1; i < size; i++)
        root = insert(root, preorder[i]);
    return root;
}

void inorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main()
{
    int preorder[] = {10, 5, 1, 7, 40, 50};
    int size = sizeof(preorder) / sizeof(preorder[0]);

    struct Node *root = constructBST(preorder, size);

    printf("Inorder Traversal of the constructed BST: ");
    inorderTraversal(root);

    return 0;
}