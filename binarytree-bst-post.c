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

    if (data > node->data)
        node->right = insert(node->right, data);
    else
        node->left = insert(node->left, data);

    return node;
}

struct Node *constructBST(int postorder[], int size)
{
    struct Node *root = NULL;
    for (int i = size - 1; i >= 0; i--)
        root = insert(root, postorder[i]);
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
    int postorder[] = {1, 7, 5, 10, 40, 50};
    int size = sizeof(postorder) / sizeof(postorder[0]);

    struct Node *root = constructBST(postorder, size);

    printf("Inorder Traversal of the constructed BST: ");
    inorderTraversal(root);

    return 0;
}