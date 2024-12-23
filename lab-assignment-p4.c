#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "avl-temp.c"

typedef int DATA;

typedef struct node
{
    DATA data;
    int left, right, parent, height;
} AVL_NODE;

typedef struct
{
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    AVL_NODE *nodelist;
} TREE;

TREE *createTree(unsigned int max_nodes)
{
    TREE *tree = (TREE *)malloc(sizeof(TREE));
    tree->num_nodes = 0;
    tree->max_nodes = max_nodes;
    tree->root = -1;
    tree->free_list = 0;
    tree->nodelist = (AVL_NODE *)malloc(max_nodes * sizeof(AVL_NODE));

    for (unsigned int i = 0; i < max_nodes - 1; i++)
    {
        tree->nodelist[i].left = i + 1;
    }
    tree->nodelist[max_nodes - 1].left = -1;
    return tree;
}

int height(TREE *tree, int index)
{
    return index != -1 ? tree->nodelist[index].height : 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int allocateNode(TREE *tree, DATA key)
{
    if (tree->free_list == -1)
        exit(1);

    int index = tree->free_list;
    tree->free_list = tree->nodelist[index].left;

    tree->nodelist[index].data = key;
    tree->nodelist[index].left = tree->nodelist[index].right = -1;
    tree->nodelist[index].parent = -1;
    tree->nodelist[index].height = 1;
    tree->num_nodes++;

    return index;
}

void deallocateNode(TREE *tree, int index)
{
    tree->nodelist[index].left = tree->free_list;
    tree->free_list = index;
    tree->num_nodes--;
}

int getBalance(TREE *tree, int index)
{
    if (index == -1)
        return 0;

    return height(tree, tree->nodelist[index].left) - height(tree, tree->nodelist[index].right);
}

int rotateRight(TREE *tree, int y)
{
    int x = tree->nodelist[y].left;
    int T2 = tree->nodelist[x].right;

    tree->nodelist[x].right = y;
    tree->nodelist[x].parent = tree->nodelist[y].parent;

    tree->nodelist[y].left = T2;
    if (T2 != -1)
        tree->nodelist[T2].parent = y;

    tree->nodelist[y].parent = x;

    tree->nodelist[y].height = max(height(tree, tree->nodelist[y].left), height(tree, tree->nodelist[y].right)) + 1;
    tree->nodelist[x].height = max(height(tree, tree->nodelist[x].left), height(tree, tree->nodelist[x].right)) + 1;

    return x;
}

int rotateLeft(TREE *tree, int x)
{
    int y = tree->nodelist[x].right;
    int T2 = tree->nodelist[y].left;

    tree->nodelist[y].left = x;
    tree->nodelist[y].parent = tree->nodelist[x].parent;

    tree->nodelist[x].right = T2;
    if (T2 != -1)
        tree->nodelist[T2].parent = x;

    tree->nodelist[x].parent = y;

    tree->nodelist[x].height = max(height(tree, tree->nodelist[x].left), height(tree, tree->nodelist[x].right)) + 1;
    tree->nodelist[y].height = max(height(tree, tree->nodelist[y].left), height(tree, tree->nodelist[y].right)) + 1;

    return y;
}

int insertAVL(TREE *tree, int index, DATA key)
{
    if (index == -1)
        return allocateNode(tree, key);

    if (key < tree->nodelist[index].data)
    {
        int left_child = insertAVL(tree, tree->nodelist[index].left, key);
        tree->nodelist[index].left = left_child;
        tree->nodelist[left_child].parent = index;
    }
    else if (key > tree->nodelist[index].data)
    {
        int right_child = insertAVL(tree, tree->nodelist[index].right, key);
        tree->nodelist[index].right = right_child;
        tree->nodelist[right_child].parent = index;
    }
    else
    {
        return index;
    }

    tree->nodelist[index].height = 1 + max(height(tree, tree->nodelist[index].left), height(tree, tree->nodelist[index].right));
    int balance = getBalance(tree, index);

    if (balance > 1 && key < tree->nodelist[tree->nodelist[index].left].data)
        return rotateRight(tree, index);

    if (balance < -1 && key > tree->nodelist[tree->nodelist[index].right].data)
        return rotateLeft(tree, index);

    if (balance > 1 && key > tree->nodelist[tree->nodelist[index].left].data)
    {
        tree->nodelist[index].left = rotateLeft(tree, tree->nodelist[index].left);
        return rotateRight(tree, index);
    }

    if (balance < -1 && key < tree->nodelist[tree->nodelist[index].right].data)
    {
        tree->nodelist[index].right = rotateRight(tree, tree->nodelist[index].right);
        return rotateLeft(tree, index);
    }

    return index;
}

void inorder(TREE *tree, int index)
{
    if (index != -1)
    {
        inorder(tree, tree->nodelist[index].left);
        printf("%d ", tree->nodelist[index].data);
        inorder(tree, tree->nodelist[index].right);
    }
}

void preorder(TREE *tree, int index)
{
    if (index != -1)
    {
        printf("%d ", tree->nodelist[index].data);
        preorder(tree, tree->nodelist[index].left);
        preorder(tree, tree->nodelist[index].right);
    }
}

int findNode(TREE *tree, int index, DATA key)
{
    if (index == -1)
        return 0;

    if (tree->nodelist[index].data == key)
        return 1;

    if (key < tree->nodelist[index].data)
        return findNode(tree, tree->nodelist[index].left, key);
    else
        return findNode(tree, tree->nodelist[index].right, key);
}

void bloomFilter(int *bloom_filter, int m, int k, int x)
{
    srand(x);
    int rand_index[k];
    // printf("%d: ", x);
    for (int i = 0; i < k; i++)
    {
        int pos = rand() % m;
        // printf("%d ", pos);
        bloom_filter[pos] = 1;
    }
    // printf("\n");
}

int bloomSearch(int *bloom_filter, int m, int k, int x)
{
    srand(x);
    int rand_index[k];
    // printf("%d: ", x);
    for (int i = 0; i < k; i++)
    {
        int pos = rand() % m;
        // printf("%d ", pos);
        if (bloom_filter[pos] == 0)
        {
            // printf("\n");
            return 0;
        }
    }
    // printf("\n");
    return 1;
}

int main(int ac, char *av[])
{
    // if (ac < 4)
    // {
    //     fprintf(stderr, "Missing required command-line arguments");
    //     return 1;
    // }

    // int m = atoi(av[1]);
    // int k = atoi(av[2]);
    // int n = ac - 3;

    // int *nums = (int *)malloc(n * sizeof(int));
    // for (int i = 0; i < n; i++)
    // {
    //     nums[i] = atoi(av[i + 3]);
    // }

    int m, k, n;
    scanf("%d %d", &m, &k);
    scanf("%d", &n);
    // printf("%d %d %d\n", m, k, n);

    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
        // printf("%d: %d ", i, nums[i]);
    }

    TREE *tree = createTree(n);
    int *bloom_filter = (int *)calloc(m, sizeof(int));
    int duplicate = 0, false_positive = 0;

    for (int i = 0; i < n; i++)
    {
        if (findNode(tree, tree->root, nums[i]))
        {
            printf("AVL %d %d\n", i, nums[i]);
            duplicate++;
        }
        else
        {
            tree->root = insertAVL(tree, tree->root, nums[i]);
        }

        if (bloomSearch(bloom_filter, m, k, nums[i]))
        {
            printf("BLOOM %d %d\n", i, nums[i]);
            if (findNode(tree, tree->root, nums[i]))
                false_positive++;
        }
        else
        {
            bloomFilter(bloom_filter, m, k, nums[i]);
        }

        // for (int k = 0; k < m; k++)
        // {
        //     printf("%d ", bloom_filter[k]);
        // }
        // printf("\n");
    }

    printf("%d\n", false_positive - duplicate);
    preorder(tree, tree->root);

    return 0;
}