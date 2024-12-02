#include <stdio.h>
#include <stdlib.h>

// AVL Node structure
typedef struct AVLNode
{
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

// Function to get height of the tree
int height(AVLNode *node)
{
    return node ? node->height : 0;
}

// Create a new node
AVLNode *createNode(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 1; // New node is initially added at leaf
    node->left = node->right = NULL;
    return node;
}

// Rotate Right
AVLNode *rotateRight(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T = x->right;
    x->right = y;
    y->left = T;
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    return x;
}

// Rotate Left
AVLNode *rotateLeft(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    return y;
}

// Get balance factor
int getBalance(AVLNode *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

// Insert into AVL Tree
AVLNode *insert(AVLNode *node, int key)
{
    if (!node)
        return createNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Update height
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get balance
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Preorder traversal
void preorder(AVLNode *root)
{
    if (root)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    AVLNode *root = NULL;

    // Example input
    int arr[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++)
    {
        root = insert(root, arr[i]);
    }

    printf("Preorder Traversal of AVL Tree: ");
    preorder(root);

    return 0;
}