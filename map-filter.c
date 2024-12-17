#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *map(void *L, unsigned int N, size_t domain_elt_size, size_t range_elt_size, void (*f)(void *input, void *output))
{
    void *R = malloc(N * range_elt_size);
    for (int i = 0; i < N; i++)
    {
        f((char *)L + i * domain_elt_size, (char *)R + i * range_elt_size);
    }

    return R;
}

int filter(void *L, unsigned int N, size_t domain_elt_size, int (*g)(void *input))
{
    int true_cnt = 0, false_cnt = 0;

    char *false_list = (char *)malloc(N * domain_elt_size);
    for (int i = 0; i < N; i++)
    {
        if (g((char *)L + i * domain_elt_size))
        {
            memcpy((char *)L + true_cnt * domain_elt_size, (char *)L + i * domain_elt_size, domain_elt_size);
            true_cnt++;
        }
        else
        {
            memcpy(false_list + false_cnt * domain_elt_size, (char *)L + i * domain_elt_size, domain_elt_size);
            false_cnt++;
        }
    }
    memcpy((char *)L + true_cnt * domain_elt_size, false_list, false_cnt * domain_elt_size);

    return true_cnt;
}