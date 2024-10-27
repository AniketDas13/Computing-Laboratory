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

// Function to create a new node
Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to initialize a linked list
LinkedList *create_linked_list()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->list_length = 0;
    return list;
}

// Function to add a node at the end
void append(LinkedList *list, int data)
{
    Node *new_node = create_node(data);
    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        Node *temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    list->list_length++;
}

// Function to rearrange the linked list: odd values before even values
void rearrange(LinkedList *list)
{
    Node *odd_head = NULL;
    Node *odd_tail = NULL;
    Node *even_head = NULL;
    Node *even_tail = NULL;
    Node *current = list->head;

    // Separate the list into odd and even lists
    while (current)
    {
        if (current->data % 2 != 0)
        { // Odd value
            if (!odd_head)
            {
                odd_head = odd_tail = current;
            }
            else
            {
                odd_tail->next = current;
                odd_tail = current;
            }
        }
        else
        { // Even value
            if (!even_head)
            {
                even_head = even_tail = current;
            }
            else
            {
                even_tail->next = current;
                even_tail = current;
            }
        }
        current = current->next;
    }

    // Combine odd and even lists
    if (odd_tail)
        odd_tail->next = even_head;
    if (even_tail)
        even_tail->next = NULL;
    list->head = odd_head ? odd_head : even_head;
}

// Function to print the linked list
void print_list(LinkedList *list)
{
    Node *temp = list->head;
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <list elements>\n", argv[0]);
        return 1;
    }

    LinkedList *list = create_linked_list();

    // Parse command-line arguments and append to list
    for (int i = 1; i < argc; i++)
    {
        int value = atoi(argv[i]);
        append(list, value);
    }

    printf("Original list: ");
    print_list(list);

    rearrange(list);

    printf("Rearranged list: ");
    print_list(list);

    return 0;
}