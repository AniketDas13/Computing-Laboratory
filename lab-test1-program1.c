#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int n;
    char c;
    // char S[126];
    // char G[50];
    int k, m, count, flag;
    double A = 0, B = 0;
    double f = 1.0 / 37.0;

    scanf("%d ", &n);
    for (int i = 0; i < n; i++)
    {
        count = 0;
        char S[126] = " ";
        char G[50] = " ";

        k = 0;
        while ((c = fgetc(stdin)) != ' ')
        {
            S[k++] = c;
        }

        k = 0;
        while ((c = fgetc(stdin)) != '\n')
        {
            G[k++] = c;
        }

        for (int j = 0; j < strlen(G); j++)
        {
            flag = 0;
            for (int l = 0; l < strlen(S); l++)
            {
                if (isalnum(G[j]) || G[j] == '_')
                {
                    if (toupper(G[j]) == toupper(S[l]))
                    {
                        // printf("%c %c\n", G[j], S[l]);
                        S[l] = '@';
                        count++;
                        if (count == strlen(S))
                        {
                            m = j + 1;
                            if (i % 2 == 0)
                                B += 1.0 / (double)m;
                            else
                                A += 1.0 / (double)m;
                            flag = 1;
                            break;
                        }
                    }
                }
                else
                {
                    if (i % 2 == 0)
                        A += f;
                    else
                        B += f;
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
                break;
        }
    }

    printf("%.6lf %.6lf", A, B);
    // for (int i = 0; i < strlen(S); i++)
    // {
    //     printf("%c", S[i]);
    // }
    // printf("\n");

    return 0;
}