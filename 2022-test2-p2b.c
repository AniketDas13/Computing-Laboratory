#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int data;
    int left;
    int right;
    int level;
} node;

typedef struct _tree
{
    int capacity;
    int num_of_nodes;
    int root;
    node *nodelist;
} tree;

void init_tree(tree *t, int n)
{
    t->capacity = 100;
    t->num_of_nodes = n;
    t->nodelist = (node *)malloc(100 * sizeof(node));
    t->root = 1;
}

void print_tree(tree *t, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("print_tree: error opening output file\n");
        return;
    }
    for (int i = 0; i < t->num_of_nodes; i++)
    {
        fprintf(fp, "%d %d %d %d\n", t->nodelist[i].data, t->nodelist[i].left, t->nodelist[i].right, t->nodelist[i].level);
    }
    fclose(fp);
}

int find_num(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i] * (1 << (n - i - 1)); // Calculate binary value from bits
    }
    return sum;
}

void remove_duplicate_leaves(tree *t, int k)
{
    int unique_0 = t->num_of_nodes;     // Index for the unique "0" leaf
    int unique_1 = t->num_of_nodes + 1; // Index for the unique "1" leaf

    // Resize the nodelist array to accommodate two additional unique nodes
    t->nodelist = (node *)realloc(t->nodelist, (t->num_of_nodes + 2) * sizeof(node));

    // Initialize unique 0 and 1 leaf nodes
    t->nodelist[unique_0] = (node){.data = 0, .left = -1, .right = -1, .level = k + 1};
    t->nodelist[unique_1] = (node){.data = 1, .left = -1, .right = -1, .level = k + 1};

    // Replace all leaves with pointers to either unique_0 or unique_1
    for (int i = 0; i < (1 << k) - 1; i++)
    {
        node *n = &t->nodelist[i];
        if (n->left >= (1 << k) - 1)
        {
            n->left = t->nodelist[n->left].data == 0 ? unique_0 : unique_1;
        }
        if (n->right >= (1 << k) - 1)
        {
            n->right = t->nodelist[n->right].data == 0 ? unique_0 : unique_1;
        }
    }

    // Update the total number of nodes in the tree
    t->num_of_nodes += 2;
}

// Main function (provided code)
int main()
{
    tree t;
    int k;
    FILE *ptr = fopen("input.txt", "r");
    if (!ptr)
    {
        printf("Error opening input file\n");
        return 1;
    }

    int c;
    int num = 0;
    while ((c = fgetc(ptr)) != '\n' && c != EOF)
    {
        num = 10 * num + (c - '0');
    }

    k = num;
    int n = (1 << (k + 1)) - 1; // Calculate the number of nodes for full binary tree
    init_tree(&t, n);

    int p = (1 << k) - 1;
    int *arr = malloc(p * sizeof(int));
    int x[3] = {-1}, m = 0, counter = 0;

    while ((c = fgetc(ptr)) != EOF)
    {
        if (c == '\n')
        {
            counter = 0;
            m = 0;
        }
        else if (counter == 2 * k)
        {
            int res = find_num(x, k);
            arr[res] = c - '0';
        }
        else if (counter % 2 == 0)
        {
            x[m++] = c - '0';
        }
        counter++;
    }

    fclose(ptr);

    for (int i = 0; i < p; i++)
    {
        t.nodelist[i].data = ceil(log2(i + 2));
        t.nodelist[i].left = 2 * i + 1;
        t.nodelist[i].right = 2 * i + 2;
        t.nodelist[i].level = t.nodelist[i].data;
    }

    for (int i = p, j = 0; i < t.num_of_nodes; i++, j++)
    {
        t.nodelist[i].data = arr[j];
        t.nodelist[i].left = -1;
        t.nodelist[i].right = -1;
        t.nodelist[i].level = k + 1;
    }

    print_tree(&t, "output2a.txt");

    // Remove duplicate leaves and create the BDD
    remove_duplicate_leaves(&t, k);

    // Print the compacted BDD tree
    print_tree(&t, "output2b.txt");

    free(t.nodelist);
    free(arr);

    return 0;
}