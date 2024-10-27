/* 2022 Lab Test 2 Qn. 2: Binary Decision Diagrams */

#include "common.h"

typedef struct {
    int data;
    int left, right, level;
} TNODE;

typedef struct {
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
    if (node->left == -1 && node->right == -1) { /* leaf */
        for (i = 0; i < index; i++)
            fprintf(fp, "%d ", buf[i]);
        fprintf(fp, "%d\n", node->data);
        return;
    }

    buf[index++] = 0;
    print_truth_table(t, node->left, fp);
    buf[index-1] = 1;
    print_truth_table(t, node->right, fp);
    index--;

    return;
}


void generate_random_boolean_function_binary_tree(TREE *t)
{
    int level, i;
    TNODE *node;

    for (i = 0, node = t->nodelist, level = 1; i < t->num_nodes / 2; i++, node++) {
        node->data = node->level = level;
        node->left = 2*i + 1;
        node->right = 2*i + 2;
        if (i == (1 << level) - 2)
            level++;
    }
    while (node - t->nodelist < t->num_nodes) {
        node->data = rand() % 2;
        node->left = -1;
        node->right = -1;
        node->level = level;
        node++;
    }
    return;
}


TREE remove_duplicate_leaves(TREE *t_in, int k)
{
    int i;
    TREE t_out;

    t_out.root = 2;
    t_out.num_nodes = (1<<k) + 1;
    if (NULL == (t_out.nodelist = Malloc(t_out.num_nodes, TNODE)))
        ERR_MESG("binary-decision-diagrams: out of memory\n");
    t_out.nodelist[0].data = 0;
    t_out.nodelist[0].left = -1;
    t_out.nodelist[0].right = -1;
    t_out.nodelist[0].level = k+1;
    t_out.nodelist[1].data = 1;
    t_out.nodelist[1].left = -1;
    t_out.nodelist[1].right = -1;
    t_out.nodelist[1].level = k+1;

    for (i = 0; i < t_in->num_nodes >> 2; i++) {
        t_out.nodelist[i+2] = t_in->nodelist[i];
        t_out.nodelist[i+2].left = t_in->nodelist[i].left + 2;
        t_out.nodelist[i+2].right = t_in->nodelist[i].right + 2;
    }

    while (i < t_in->num_nodes >> 1) {
        t_out.nodelist[i+2] = t_in->nodelist[i];
        t_out.nodelist[i+2].left = t_in->nodelist[2*i+1].data;
        t_out.nodelist[i+2].right = t_in->nodelist[2*i+2].data;
        i++;   
    }

    return t_out;
}


int main(int ac, char *av[])
{
    unsigned int k;
    FILE *fp;
    TREE t;

    if (ac < 2)
        ERR_MESG("Usage: binary-decision-diagrams <number of boolean variables>");
    k = (unsigned) atoi(av[1]);
    if (k > 20)
        ERR_MESG("Number of boolean variables too large (> 20)");

    t.root = 0;
    t.num_nodes = (1 << (k+1)) - 1;
    if (NULL == (t.nodelist = Malloc(t.num_nodes, TNODE)))
        ERR_MESG("binary-decision-diagrams: out of memory\n");
    generate_random_boolean_function_binary_tree(&t);
    if (NULL == (fp = fopen("input2.txt", "w")))
        ERR_MESG("print_tree: error opening output file");
    print_truth_table(&t, 0, fp);
    fclose(fp);

    print_tree(&t, "output2a.txt");

    t = remove_duplicate_leaves(&t, k);
    print_tree(&t, "output2b.txt");

    return 0;
}
