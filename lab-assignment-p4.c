#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl-temp.c"

void bloomFilter(unsigned char *bloom_filter, int m, int k, int x)
{
    srand(x);
    for (int i = 0; i < k; i++)
    {
        int pos = rand() % m;
        bloom_filter[pos] = 1;
        // printf("%d ", pos);
    }
    // printf("\n");
}

int bloomSearch(unsigned char *bloom_filter, int m, int k, int x)
{
    srand(x);
    for (int i = 0; i < k; i++)
    {
        int pos = rand() % m;
        if (bloom_filter[pos] == 0)
        {
            // printf("\n");
            return 0;
        }
        // printf("%d ", pos);
    }
    // printf("\n");
    return 1;
}

int main(int ac, char *av[])
{
    if (ac < 4)
    {
        fprintf(stderr, "Missing required command-line arguments");
        return 1;
    }

    int m = atoi(av[1]);
    int k = atoi(av[2]);
    int n = ac - 3;

    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        nums[i] = atoi(av[i + 3]);
    }

    AVL_NODE *root = NULL;

    clock_t start_avl = clock();
    // printf("%ld\n", start_avl);
    for (int i = 0; i < n; i++)
    {
        int inserted = 0;
        root = insertAVL(root, nums[i], &inserted);
        if (inserted)
        {
            printf("INSERTED: %d\n", nums[i]);
            // inorder(root);
            // printf("\n");
        }
        else
        {
            printf("DUPLICATE: %d\n", nums[i]);
        }
    }
    clock_t end_avl = clock();
    // printf("%ld\n", end_avl);

    unsigned char *bloom_filter = (unsigned char *)calloc(m, sizeof(unsigned char));

    clock_t start_bloom = clock();
    // printf("%ld\n", start_bloom);
    for (int i = 0; i < n; i++)
    {
        if (bloomSearch(bloom_filter, m, k, nums[i]))
        {
            printf("DUPLICATE: %d\n", nums[i]);
        }
        else
        {
            bloomFilter(bloom_filter, m, k, nums[i]);
            printf("INSERTED: %d\n", nums[i]);
        }

        // for (int k = 0; k < m; k++)
        // {
        //     printf("%d ", bloom_filter[k]);
        // }
        // printf("\n");
    }
    clock_t end_bloom = clock();
    // printf("%ld\n", end_bloom);

    fprintf(stderr, "AVL Tree: size: %d, time: %.6f secs\n", countNodes(root), (double)(end_avl - start_avl) / CLOCKS_PER_SEC);
    fprintf(stderr, "Bloom Filter: size: %d, time: %.6f secs\n", m, (double)(end_bloom - start_bloom) / CLOCKS_PER_SEC);

    return 0;
}