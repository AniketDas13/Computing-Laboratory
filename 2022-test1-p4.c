#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *a)
{
    int length = strlen(a);

    for (int i = 0; i < length / 2; i++)
    {
        char temp;
        temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}

typedef struct
{
    int size;     // Size of the list
    char **array; // Dynamically allocated array of strings
} LIST;

// Function to create an empty list
LIST create_list()
{
    LIST L;
    L.size = 0;
    L.array = NULL;
    return L;
}

// Function to print the list
void print_list(LIST L)
{
    printf("(");
    for (int i = 0; i < L.size; i++)
    {
        if (i > 0)
        {
            printf(",");
        }
        printf("%s", L.array[i]);
    }
    printf(")\n");
}

// Function to append a string to the list
LIST append(LIST L, char *a)
{
    L.size++;
    L.array = realloc(L.array, L.size * sizeof(char *));
    L.array[L.size - 1] = malloc(10 * sizeof(char));
    strcpy(L.array[L.size - 1], a);
    return L;
}

// Function to prepend a string to the list
LIST prepend(LIST L, char *a)
{
    L.size++;
    L.array = realloc(L.array, L.size * sizeof(char *));
    for (int i = L.size - 1; i > 0; i--)
    {
        L.array[i] = L.array[i - 1];
    }
    L.array[0] = malloc(10 * sizeof(char));
    strcpy(L.array[0], a);
    return L;
}

// Function to delete the last string from the list
LIST deletelast(LIST L)
{
    if (L.size > 0)
    {
        free(L.array[L.size - 1]);
        L.size--;
        L.array = realloc(L.array, L.size * sizeof(char *));
    }
    return L;
}

// Function to delete the first string from the list
LIST deletefirst(LIST L)
{
    if (L.size > 0)
    {
        free(L.array[0]);
        for (int i = 0; i < L.size - 1; i++)
        {
            L.array[i] = L.array[i + 1];
        }
        L.size--;
        L.array = realloc(L.array, L.size * sizeof(char *));
    }
    return L;
}

// Function to delete all occurrences of a string from the list
LIST deleteall(LIST L, char *a)
{
    for (int i = 0; i < L.size;)
    {
        if (strcmp(L.array[i], a) == 0)
        {
            free(L.array[i]);
            for (int j = i; j < L.size - 1; j++)
            {
                L.array[j] = L.array[j + 1];
            }
            L.size--;
            L.array = realloc(L.array, L.size * sizeof(char *));
        }
        else
        {
            i++;
        }
    }
    return L;
}

int main()
{
    // Test sequence as shown in the output in the PDF
    LIST L = create_list(); // Create an empty list
    print_list(L);

    L = append(L, "apple");
    print_list(L);

    L = append(L, "lemon");
    print_list(L);

    L = append(L, "banana");
    print_list(L);

    L = append(L, "pineapple");
    print_list(L);

    L = append(L, "pear");
    print_list(L);

    L = append(L, "mango");
    print_list(L);

    L = append(L, "orange");
    print_list(L);

    L = append(L, "cherry");
    print_list(L);

    L = append(L, "banana");
    print_list(L);

    L = append(L, "pineapple");
    print_list(L);

    L = prepend(L, "apple");
    print_list(L);

    L = prepend(L, "banana");
    print_list(L);

    L = prepend(L, "orange");
    print_list(L);

    L = prepend(L, "plum");
    print_list(L);

    L = deletefirst(L);
    print_list(L);

    L = deletefirst(L);
    print_list(L);

    L = deletelast(L);
    print_list(L);

    L = deletelast(L);
    print_list(L);

    L = deleteall(L, "banana");
    print_list(L);

    L = deleteall(L, "apple");
    print_list(L);

    L = deleteall(L, "cherry");
    print_list(L);

    return 0;
}