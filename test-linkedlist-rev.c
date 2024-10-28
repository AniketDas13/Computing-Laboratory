#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    int list_length;
} LinkedList;

void reverseList(LinkedList *list)
{
    Node *prev = NULL, *current = list->head, *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;
}

void printList(LinkedList *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void push(LinkedList *list, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->list_length++;
}

int main()
{
    LinkedList list;
    list.head = NULL;
    list.list_length = 0;

    push(&list, 20);
    push(&list, 4);
    push(&list, 15);
    push(&list, 85);

    printf("Original List: ");
    printList(&list);

    reverseList(&list);

    printf("Reversed List: ");
    printList(&list);

    return 0;
}