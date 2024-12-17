#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left, *right;
    int height;
} AVL_NODE;

AVL_NODE *createNode(int key)
{
    AVL_NODE *node = (AVL_NODE *)malloc(sizeof(AVL_NODE));
    node->data = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int height(AVL_NODE *node)
{
    return node ? node->height : 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

AVL_NODE *rotateRight(AVL_NODE *y)
{
    AVL_NODE *x = y->left;
    AVL_NODE *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVL_NODE *rotateLeft(AVL_NODE *x)
{
    AVL_NODE *y = x->right;
    AVL_NODE *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVL_NODE *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

AVL_NODE *insertAVL(AVL_NODE *root, int key, int *inserted)
{
    if (!root)
    {
        *inserted = 1;
        return createNode(key);
    }

    if (key < root->data)
    {
        root->left = insertAVL(root->left, key, inserted);
    }
    else if (key > root->data)
    {
        root->right = insertAVL(root->right, key, inserted);
    }
    else
    {
        *inserted = 0;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && key < root->left->data)
    {
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->data)
    {
        return rotateLeft(root);
    }
    if (balance > 1 && key > root->left->data)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->data)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int countNodes(AVL_NODE *root)
{
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void inorder(AVL_NODE *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}