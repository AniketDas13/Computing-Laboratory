/* 2022 Lab Test 2 Qn. 2: Binary Decision Diagrams */

#include "common.h"

typedef struct
{
    int data;
    int left, right, level;
} TNODE;

typedef struct
{
    int root, num_nodes;
    TNODE *nodelist;
} TREE;

void print_tree(TREE *t, char *filename)
{
    FILE *fp;
    TNODE *node;

    if (NULL == (fp = fopen(filename, "w")))
        ERR_MESG("print_tree: error opening output file");
    for (node = t->nodelist; node - t->nodelist < t->num_nodes; node++)
        fprintf(fp, "%d %d %d %d\n", node->data, node->left, node->right,
                node->level);
    fclose(fp);
    return;
}

void print_truth_table(TREE *t, int root, FILE *fp)
{
    static char buf[32];
    static int index;
    int i;
    TNODE *node;

    assert(root != -1);
    node = t->nodelist + root;
    if (node->left == -1 && node->right == -1)
    { /* leaf */
        for (i = 0; i < index; i++)
            fprintf(fp, "%d ", buf[i]);
        fprintf(fp, "%d\n", node->data);
        return;
    }

    buf[index++] = 0;
    print_truth_table(t, node->left, fp);
    buf[index - 1] = 1;
    print_truth_table(t, node->right, fp);
    index--;

    return;
}

void generate_random_boolean_function_binary_tree(TREE *t, int root, int level, int k)
{
    TNODE *node = t->nodelist + root;

    node->level = level;
    if (k == 0)
    { /* at leaf */
        node->data = rand() % 2;
        node->left = -1;
        node->right = -1;
        return;
    }
    node->data = level;
    node->left = root + 1;
    node->right = root + (1 << k);
    generate_random_boolean_function_binary_tree(t, node->left, level + 1, k - 1);
    generate_random_boolean_function_binary_tree(t, node->right, level + 1, k - 1);
    return;
}

void remove_duplicate_leaves_recursively(TREE *t_in, TREE *t_out, int root, int k)
{
    TNODE *in_node, *out_node;
    static int first_free_index = 2;

    in_node = t_in->nodelist + root;
    out_node = t_out->nodelist + first_free_index++;

    if (in_node->level == k + 1) /* leaf; just skip */
        return;

    *out_node = *in_node;

    if (in_node->level == k)
    {
        out_node->left = t_in->nodelist[in_node->left].data;
        out_node->right = t_in->nodelist[in_node->right].data;
        return;
    }

    /* Since the tree was constructed in pre-order, left child (if
     * exists) is always the next element in the array */
    out_node->left = first_free_index;
    remove_duplicate_leaves_recursively(t_in, t_out, in_node->left, k);
    out_node->right = first_free_index;
    remove_duplicate_leaves_recursively(t_in, t_out, in_node->right, k);

    return;
}

TREE remove_duplicate_leaves(TREE *t_in, int k)
{
    TREE t_out;

    t_out.root = 2;
    t_out.num_nodes = (1 << k) + 1;
    if (NULL == (t_out.nodelist = Malloc(t_out.num_nodes, TNODE)))
        ERR_MESG("binary-decision-diagrams: out of memory\n");
    t_out.nodelist[0].data = 0;
    t_out.nodelist[0].left = -1;
    t_out.nodelist[0].right = -1;
    t_out.nodelist[0].level = k + 1;
    t_out.nodelist[1].data = 1;
    t_out.nodelist[1].left = -1;
    t_out.nodelist[1].right = -1;
    t_out.nodelist[1].level = k + 1;

    remove_duplicate_leaves_recursively(t_in, &t_out, 0, k);

    return t_out;
}

int main(int ac, char *av[])
{
    unsigned int k;
    FILE *fp;
    TREE t;

    if (ac < 2)
        ERR_MESG("Usage: binary-decision-diagrams <number of boolean variables>");
    k = (unsigned)atoi(av[1]);
    if (k > 20)
        ERR_MESG("Number of boolean variables too large (> 20)");

    t.root = 0;
    t.num_nodes = (1 << (k + 1)) - 1;
    if (NULL == (t.nodelist = Malloc(t.num_nodes, TNODE)))
        ERR_MESG("binary-decision-diagrams: out of memory\n");
    generate_random_boolean_function_binary_tree(&t, 0, 1, k);
    if (NULL == (fp = fopen("input2.txt", "w")))
        ERR_MESG("print_tree: error opening output file");
    print_truth_table(&t, 0, fp);
    fclose(fp);

    print_tree(&t, "output2a.txt");

    t = remove_duplicate_leaves(&t, k);
    print_tree(&t, "output2b.txt");

    return 0;
}