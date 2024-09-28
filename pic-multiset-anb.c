#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_256 123

int main()
{
    int freqA[CHAR_256];
    int freqB[CHAR_256];

    memset(freqA, 0, 123 * sizeof(int));
    memset(freqB, 0, 123 * sizeof(int));

    char *A = (char *)malloc(100 * sizeof(char));
    char *B = (char *)malloc(100 * sizeof(char));

    printf("Enter the first array : ");
    scanf("%s", A);
    printf("\nEnter the second array : ");
    scanf("%s", B);

    for (int i = 0; i < strlen(A); i++)
    {
        freqA[A[i]]++;
    }

    for (int i = 0; i < strlen(B); i++)
    {
        freqB[B[i]]++;
    }

    if (strlen(A) != strlen(B))
    {
        printf("\nMultisets of A and B are not equal.");
    }
    else
    {
        int flag = 1;
        for (int i = 0; i < strlen(A); i++)
        {
            if (freqA[A[i]] != freqB[A[i]])
            {
                flag = 0;
                break;
            }
        }

        if (flag == 1)
        {
            printf("\nMultisets of A and B are equal.");
        }
        else
        {
            printf("\nMultisets of A and B are not equal.");
        }
    }

    return 0;
}