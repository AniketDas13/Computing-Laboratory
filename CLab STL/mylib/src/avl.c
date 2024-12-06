#include "avl.h"

// Function to initialize the tree
void init_tree(TREE *T, int capacity, size_t data_size, int (*compare)(const void *, const void *), void (*print)(const void *))
{
    T->capacity = capacity;
    T->num_nodes = 0;
    T->root = -1;
    T->data_size = data_size;
    T->nodelist = (TNODE *)malloc(capacity * sizeof(TNODE));
    T->compare = compare;
    T->print = print;
}

// Function to get the height of a node
int get_height(TREE *T, int index)
{
    return (index == -1) ? 0 : T->nodelist[index].height;
}

// Function to calculate the balance factor of a node
int get_balance(TREE *T, int index)
{
    if (index == -1)
        return 0;
    return get_height(T, T->nodelist[index].left) - get_height(T, T->nodelist[index].right);
}

// Function to update the height of a node
void update_height(TREE *T, int index)
{
    if (index != -1)
    {
        T->nodelist[index].height = 1 + ((get_height(T, T->nodelist[index].left) > get_height(T, T->nodelist[index].right))
                                             ? get_height(T, T->nodelist[index].left)
                                             : get_height(T, T->nodelist[index].right));
    }
}

// Function to perform a right rotation
int right_rotate(TREE *T, int y)
{
    int x = T->nodelist[y].left;
    int T2 = T->nodelist[x].right;

    // Perform rotation
    T->nodelist[x].right = y;
    T->nodelist[y].left = T2;

    // Update parent pointers
    if (T2 != -1)
        T->nodelist[T2].parent = y;
    T->nodelist[x].parent = T->nodelist[y].parent;
    T->nodelist[y].parent = x;

    // Update heights
    update_height(T, y);
    update_height(T, x);

    return x; // Return new root
}

// Function to perform a left rotation
int left_rotate(TREE *T, int x)
{
    int y = T->nodelist[x].right;
    int T2 = T->nodelist[y].left;

    // Perform rotation
    T->nodelist[y].left = x;
    T->nodelist[x].right = T2;

    // Update parent pointers
    if (T2 != -1)
        T->nodelist[T2].parent = x;
    T->nodelist[y].parent = T->nodelist[x].parent;
    T->nodelist[x].parent = y;

    // Update heights
    update_height(T, x);
    update_height(T, y);

    return y; // Return new root
}

// Function to insert a new node into the AVL tree
int insert_node(TREE *T, int root, void *data)
{
    if (root == -1)
    {
        if (T->num_nodes >= T->capacity)
        {
            fprintf(stderr, "Tree capacity exceeded\n");
            return root;
        }
        int index = T->num_nodes++;
        T->nodelist[index].data = malloc(T->data_size);
        memcpy(T->nodelist[index].data, data, T->data_size);
        T->nodelist[index].left = T->nodelist[index].right = -1;
        T->nodelist[index].parent = -1;
        T->nodelist[index].height = 1;
        return index;
    }

    // Recursively insert into left or right subtree
    if (T->compare(data, T->nodelist[root].data) < 0)
    {
        int left_child = insert_node(T, T->nodelist[root].left, data);
        T->nodelist[root].left = left_child;
        T->nodelist[left_child].parent = root;
    }
    else if (T->compare(data, T->nodelist[root].data) > 0)
    {
        int right_child = insert_node(T, T->nodelist[root].right, data);
        T->nodelist[root].right = right_child;
        T->nodelist[right_child].parent = root;
    }
    else
    {
        return root; // Duplicates not allowed
    }

    // Update height of this node
    update_height(T, root);

    // Get balance factor to check for imbalance
    int balance = get_balance(T, root);

    // Perform rotations to fix imbalance
    if (balance > 1 && T->compare(data, T->nodelist[T->nodelist[root].left].data) < 0)
    {
        return right_rotate(T, root); // Left Left case
    }
    if (balance < -1 && T->compare(data, T->nodelist[T->nodelist[root].right].data) > 0)
    {
        return left_rotate(T, root); // Right Right case
    }
    if (balance > 1 && T->compare(data, T->nodelist[T->nodelist[root].left].data) > 0)
    {
        T->nodelist[root].left = left_rotate(T, T->nodelist[root].left); // Left Right case
        return right_rotate(T, root);
    }
    if (balance < -1 && T->compare(data, T->nodelist[T->nodelist[root].right].data) < 0)
    {
        T->nodelist[root].right = right_rotate(T, T->nodelist[root].right); // Right Left case
        return left_rotate(T, root);
    }

    return root; // Return unchanged root
}

// Function to search for a node in the AVL tree
int search(TREE *T, int root, void *data)
{
    if (root == -1)
    {
        return -1; // Data not found
    }

    int cmp = T->compare(data, T->nodelist[root].data);
    if (cmp == 0)
    {
        return root; // Data found
    }
    else if (cmp < 0)
    {
        return search(T, T->nodelist[root].left, data); // Search in the left subtree
    }
    else
    {
        return search(T, T->nodelist[root].right, data); // Search in the right subtree
    }
}

// Function to print the tree in pre-order
void preorder(TREE *T, int root)
{
    if (root == -1)
        return;
    T->print(T->nodelist[root].data);
    preorder(T, T->nodelist[root].left);
    preorder(T, T->nodelist[root].right);
}

// Function to print the tree in in-order traversal
void inorder(TREE *T, int root)
{
    if (root == -1)
        return;
    inorder(T, T->nodelist[root].left);
    T->print(T->nodelist[root].data);
    inorder(T, T->nodelist[root].right);
}

// Function to print the tree in post-order traversal
void postorder(TREE *T, int root)
{
    if (root == -1)
        return;
    postorder(T, T->nodelist[root].left);
    postorder(T, T->nodelist[root].right);
    T->print(T->nodelist[root].data);
}

// Function to free the tree
void free_tree(TREE *T)
{
    for (int i = 0; i < T->num_nodes; i++)
    {
        free(T->nodelist[i].data);
    }
    free(T->nodelist);
}
