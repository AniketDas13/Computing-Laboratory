#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new tree node
Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Utility function to search for an element in an array
int search(int arr[], int start, int end, int value)
{
    for (int i = start; i <= end; i++)
    {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

// Function to construct the BST from Preorder traversal
Node *construct_bst_from_preorder(int preorder[], int *preorder_index, int min, int max, int size)
{
    if (*preorder_index >= size)
        return NULL;

    int root_data = preorder[*preorder_index];
    if (root_data < min || root_data > max)
        return NULL;

    // Create the root node with the current value
    Node *root = create_node(root_data);
    (*preorder_index)++;

    // Recursively construct the left and right subtrees
    root->left = construct_bst_from_preorder(preorder, preorder_index, min, root_data - 1, size);
    root->right = construct_bst_from_preorder(preorder, preorder_index, root_data + 1, max, size);

    return root;
}

// Function to construct the Binary Tree from Inorder and Postorder traversals
Node *construct_tree_from_inorder_postorder(int inorder[], int postorder[], int inorder_start, int inorder_end, int *postorder_index)
{
    if (inorder_start > inorder_end)
        return NULL;

    // The last element in postorder is the root of the current subtree
    int root_data = postorder[(*postorder_index)--];
    Node *root = create_node(root_data);

    // If there are no children, return the node
    if (inorder_start == inorder_end)
        return root;

    // Find the index of this root in inorder to split into left and right subtrees
    int inorder_index = search(inorder, inorder_start, inorder_end, root_data);

    // Recursively build the right and left subtrees
    root->right = construct_tree_from_inorder_postorder(inorder, postorder, inorder_index + 1, inorder_end, postorder_index);
    root->left = construct_tree_from_inorder_postorder(inorder, postorder, inorder_start, inorder_index - 1, postorder_index);

    return root;
}

// Function to check if two trees are mirror images of each other
int are_mirrors(Node *tree1, Node *tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return 1;

    if (tree1 == NULL || tree2 == NULL)
        return 0;

    return (tree1->data == tree2->data) &&
           are_mirrors(tree1->left, tree2->right) &&
           are_mirrors(tree1->right, tree2->left);
}

// Function to free memory of the tree
void free_tree(Node *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Main function
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    if (n != m)
    {
        printf("NOT MIRROR TWIN\n");
        return 0;
    }

    int preorder[n], inorder[n], postorder[n];

    // Read preorder traversal of BST
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &preorder[i]);
    }

    // Read inorder traversal of binary tree
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &inorder[i]);
    }

    // Read postorder traversal of binary tree
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &postorder[i]);
    }

    // Construct BST from preorder
    int preorder_index = 0;
    Node *bst_root = construct_bst_from_preorder(preorder, &preorder_index, -__INT_MAX__, __INT_MAX__, n);

    // Construct Binary Tree from inorder and postorder
    int postorder_index = n - 1;
    Node *binary_tree_root = construct_tree_from_inorder_postorder(inorder, postorder, 0, n - 1, &postorder_index);

    // Check if they are mirror twins
    if (are_mirrors(bst_root, binary_tree_root))
    {
        printf("MIRROR TWIN\n");
    }
    else
    {
        printf("NOT MIRROR TWIN\n");
    }

    // Free the allocated memory for both trees
    free_tree(bst_root);
    free_tree(binary_tree_root);

    return 0;
}