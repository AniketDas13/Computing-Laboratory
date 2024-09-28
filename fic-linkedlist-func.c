#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedlist
{
    int n;
    char **a;
} list;

list head;
int first = -1;
int last = -1;

void createlist()
{
    head.n = 10;
    char **b;
    int i;

    for (i = 0; i < head.n; i++)
    {
        b[i] = (char *)malloc(9 * sizeof(char));
    }
    for (i = 0; i < head.n; i++)
    {
        b[i] = NULL;
    }

    head.a = b;
}

void printlist()
{
    int num = head.n;
    printf("(");

    for (int i = 0; i < num; i++)
    {
        if (head.a[i] != NULL)
        {
            printf("%s,", head.a[i]);
        }
    }

    printf(")");
    printf("\n");
}

void append(char *a)
{
    if (first == -1 && last == -1)
    {
        first++;
        last++;
        head.a[last] = a;
    }
    else
    {
        last++;
        head.a[last] = a;
    }

    printlist();
}

void prepend(char *a)
{
    for (int i = last + 1; i > first; i--)
    {
        head.a[i] = head.a[i - 1];
    }

    head.a[0] = a;
    first = 0;
    last++;
    printlist();
}
void deletelast()
{
    head.a[last] = NULL;
    last--;
    printlist();
}
void deletefirst()
{
    for (int i = first; i < last; i++)
    {
        head.a[i] = head.a[i + 1];
    }

    head.a[last] = NULL;
    last--;
    printlist();
}

void delete(int index)
{
    for (int i = index; i < last; i++)
    {
        head.a[i] = head.a[i + 1];
    }

    head.a[last] = NULL;
    last--;
}

void deleteall(char *b)
{
    for (int i = first; i <= last; i++)
    {
        if (strcmp(head.a[i], b) == 0)
        {
            delete (i);
        }
        if (head.a[i] == NULL)
        {
            break;
        }
    }

    printlist();
}

int main()
{
    createlist();
    printlist();

    append("apple");
    append("lemon");
    append("banana");
    append("pineapple");
    append("pear");
    append("apple");
    append("orange");
    append("cherry");
    append("mango");
    prepend("Durga");

    deletelast();
    deletefirst();
    deleteall("apple");

    return 0;
}