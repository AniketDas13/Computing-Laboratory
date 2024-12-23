#include "common.h"
// #include "map-filter.c"
// #include "map-filter-functions.c"

/*---------------------------------------------------------------------------
 * MAPS
 */
void map1(void *input, void *output)
{ /* char to char */
    char in = *(char *)input;
    char *out = output;
    if (isdigit(in))
        *out = 'A' + in - '0';
    else if (isalpha(in))
        *out = '0' + in % 10;
    else
        *out = in;
    return;
}

void map2(void *input, void *output)
{ /* char * to int */
    char *out = *(char **)input;
    int sum = 0, *ptr = output;
    while (*out)
        sum += *out++;
    *ptr = sum;
    return;
}

void map3(void *input, void *output)
{ /* int to float */
    int in = *(int *)input;
    float f = in, *fp = output;
    *fp = sqrtf(f);
    return;
}

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 * FILTERS
 */
int filter1(void *input)
{ /* is odd */
    int in = *(int *)input;
    return in % 2;
}

int filter2(void *input)
{ /* is vowel */
    char in = tolower(*(char *)input);
    return (in == 'a' || in == 'e' || in == 'i' || in == 'o' || in == 'u');
}

int filter3(void *input)
{
    return 0;
}
/*---------------------------------------------------------------------------*/

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

int main(int ac, char *av[])
{
    char inbuf_char[] = "This is a test string, containing various characters\n",
         *inbuf_strings[] = {
             "You should upload a C file",
             "(say map-filter.c) containing",
             "\n\t\byour implementation of \"map-filter.c\"",
         },
         *out1;
    int inbuf_int[] = {12394, 982763, 3765, 8761, 38971, 802948}, i, *out2;
    int n;
    float *out3;

    out1 = map(inbuf_char, sizeof(inbuf_char) / sizeof(inbuf_char[0]), sizeof(char), sizeof(char), map1);
    for (i = 0; i < sizeof(inbuf_char) / sizeof(inbuf_char[0]); i++)
        printf("%d ", out1[i]);
    putchar('\n');

    out2 = map(inbuf_strings, sizeof(inbuf_strings) / sizeof(char *), sizeof(char *), sizeof(int), map2);
    for (i = 0; i < sizeof(inbuf_strings) / sizeof(char *); i++)
        printf("%d ", out2[i]);
    putchar('\n');

    out3 = map(inbuf_int, sizeof(inbuf_int) / sizeof(int), sizeof(int), sizeof(float), map3);
    for (i = 0; i < sizeof(inbuf_int) / sizeof(int); i++)
        printf("%f ", out3[i]);
    putchar('\n');

    n = filter(inbuf_int, sizeof(inbuf_int) / sizeof(int), sizeof(int), filter1);
    for (i = 0; i < sizeof(inbuf_int) / sizeof(int); i++)
        printf("%d ", inbuf_int[i]);
    printf("%d\n", n);

    n = filter(inbuf_char, strlen(inbuf_char), sizeof(char), filter2);
    for (i = 0; i <= strlen(inbuf_char); i++)
        printf("%c ", inbuf_char[i]);
    printf("%d\n", n);

    free(out1);
    free(out2);
    free(out3);
    return 0;
}