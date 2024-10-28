#include "common.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    int left;
    int right;
    int level;
} node;

typedef struct _tree
{
    int root;
    int capacity;
    int num_of_nodes;
    node *nodelist;
} tree;

void init_tree(tree *t, int n)
{
    t->capacity = 100;
    t->num_of_nodes = n;
    t->nodelist = (node *)malloc(100 * sizeof(node));
    t->root = 0;
    return;
}

void print_tree(tree *t, char *filename)
{
    FILE *fp;
    node *node;
    if (NULL == (fp = fopen(filename, "w")))
        printf("print_tree: error opening output file");
    for (node = t->nodelist; node - t->nodelist < t->num_of_nodes; node++)
    {
        fprintf(fp, "%d %d %d %d\n", node->data, node->left, node->right, node->level);
    }
    fclose(fp);
    return;
}

int find_num(int *arr, int n)
{
    int sum = 0;
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        sum += pow(2, n - 1 - i) * arr[i];
    }
    return sum;
}

int main()
{
    tree t;
    int k;
    FILE *ptr = fopen("input.txt", "r");
    int c;
    int num = 0;

    while ('\n' != (c = fgetc(ptr)))
    {
        num = 10 * num + (c - '0');
    }

    k = num;
    int n = pow(2, k + 1) - 1; //(1 << (k + 1)) - 1
    init_tree(&t, n);

    int i;
    int p = pow(2, k) - 1; // internal nodes
    int counter = 0;
    int *arr = malloc((p + 1) * sizeof(int)); // leaf nodes
    int x[k];
    int m = 0;

    while (EOF != (c = fgetc(ptr)))
    {
        if (c == '\n')
        {
            counter = 0;
            m = 0;
        }
        else if (counter == (2 * k))
        {
            int res = find_num(x, k);
            arr[res] = (c - '0');
        }
        else
        {
            if (counter % 2 == 0)
            {
                x[m++] = (c - '0');
            }
            counter++;
        }
    }

    fclose(ptr);

    for (i = 0; i < p; i++)
    {
        t.nodelist[i].data = ceil(log(i + 2) / log(2));
        t.nodelist[i].left = 2 * i + 1;
        t.nodelist[i].right = 2 * i + 2;
        t.nodelist[i].level = t.nodelist[i].data;
    }

    int j = 0;
    for (i = p; i <= t.num_of_nodes - 1; i++)
    {
        t.nodelist[i].data = arr[j++];
        t.nodelist[i].left = -1;
        t.nodelist[i].right = -1;
        t.nodelist[i].level = k + 1;
    }

    print_tree(&t, "output2a.txt");

    return 0;
}