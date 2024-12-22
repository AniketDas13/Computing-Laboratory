#include "common.h"
#include "map-filter.c"
#include "map-filter-functions.c"

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
    for (i = 0; i < strlen(inbuf_char); i++)
        printf("%c ", inbuf_char[i]);
    printf("%d\n", n);

    free(out1);
    free(out2);
    free(out3);
    return 0;
}