#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left, *right;
};

/* Function to create a new node */
struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

/* Function to check if two trees are mirror images of each other */
int isMirror(struct Node *tree1, struct Node *tree2)
{
    // If both trees are empty, they are mirror images
    if (tree1 == NULL && tree2 == NULL)
        return 1; // 1 represents true

    // If one is empty and the other is not, they are not mirror images
    if (tree1 == NULL || tree2 == NULL)
        return 0; // 0 represents false

    // Check if the root node values are equal
    if (tree1->data != tree2->data)
        return 0; // 0 represents false

    // Check if the left subtree of tree1 is a mirror image of the right subtree of tree2
    int leftSubtreesMirror = isMirror(tree1->left, tree2->right);

    // Check if the right subtree of tree1 is a mirror image of the left subtree of tree2
    int rightSubtreesMirror = isMirror(tree1->right, tree2->left);

    return leftSubtreesMirror && rightSubtreesMirror; // Logical AND using bitwise AND operator
}

int main()
{
    // Create two trees
    struct Node *tree1 = newNode(1);
    tree1->left = newNode(2);
    tree1->right = newNode(3);
    tree1->left->left = newNode(4);
    tree1->left->right = newNode(5);

    struct Node *tree2 = newNode(1);
    tree2->right = newNode(2);
    tree2->left = newNode(3);
    tree2->right->right = newNode(4);
    tree2->right->left = newNode(5);

    if (isMirror(tree1, tree2))
        printf("The trees are mirror images of each other.\n");
    else
        printf("The trees are not mirror images of each other.\n");

    return 0;
}