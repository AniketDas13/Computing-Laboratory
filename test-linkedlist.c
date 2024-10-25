#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

// Function to create a new node
struct Node *newNode(int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the beginning
void push(struct Node **head_ref, int new_data)
{
    struct Node *new_node = newNode(new_data);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to insert a new node after a given node
void insertAfter(struct Node *prev_node, int new_data)
{
    if (prev_node == NULL)
    {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct Node *new_node = newNode(new_data);
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

// Function to append a new node at the end
void append(struct Node **head_ref, int new_data)
{
    struct Node *new_node = newNode(new_data);

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    struct Node *last = *head_ref;
    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

// Function to print the linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    struct Node *head = NULL;

    push(&head, 10);
    push(&head, 20);
    push(&head, 30);

    printf("Created Linked List is: ");
    printList(head);

    insertAfter(head->next, 40);

    printf("Linked List after inserting 40: ");
    printList(head);

    append(&head, 50);

    printf("Linked List after appending 50: ");
    printList(head);

    return 0;
}