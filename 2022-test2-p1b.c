#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Node
{
    int data;
    int next_node_index;
} Node;

typedef struct LinkedList
{
    Node nodes[MAX_SIZE];
    int head;
    int list_length;
} LinkedList;

// Function to initialize a linked list
void initialize_linked_list(LinkedList *list)
{
    list->head = -1;
    list->list_length = 0;
}

// Function to add a node at the end
void append(LinkedList *list, int data)
{
    if (list->list_length >= MAX_SIZE)
    {
        printf("List is full\n");
        return;
    }

    int new_index = list->list_length;
    list->nodes[new_index].data = data;
    list->nodes[new_index].next_node_index = -1;

    if (list->head == -1)
    {
        list->head = new_index;
    }
    else
    {
        int temp = list->head;
        while (list->nodes[temp].next_node_index != -1)
        {
            temp = list->nodes[temp].next_node_index;
        }
        list->nodes[temp].next_node_index = new_index;
    }

    list->list_length++;
}

// Function to rearrange the linked list: odd values before even values
void rearrange(LinkedList *list)
{
    int odd_head = -1, odd_tail = -1;
    int even_head = -1, even_tail = -1;

    int current = list->head;

    // Separate the list into odd and even lists
    while (current != -1)
    {
        if (list->nodes[current].data % 2 != 0)
        { // Odd value
            if (odd_head == -1)
            {
                odd_head = odd_tail = current;
            }
            else
            {
                list->nodes[odd_tail].next_node_index = current;
                odd_tail = current;
            }
        }
        else
        { // Even value
            if (even_head == -1)
            {
                even_head = even_tail = current;
            }
            else
            {
                list->nodes[even_tail].next_node_index = current;
                even_tail = current;
            }
        }
        current = list->nodes[current].next_node_index;
    }

    // Combine odd and even lists
    if (odd_tail != -1)
        list->nodes[odd_tail].next_node_index = even_head;
    if (even_tail != -1)
        list->nodes[even_tail].next_node_index = -1;

    list->head = (odd_head != -1) ? odd_head : even_head;
}

// Function to print the linked list
void print_list(LinkedList *list)
{
    int temp = list->head;
    while (temp != -1)
    {
        printf("%d ", list->nodes[temp].data);
        temp = list->nodes[temp].next_node_index;
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

    LinkedList list;
    initialize_linked_list(&list);

    // Parse command-line arguments and append to list
    for (int i = 1; i < argc; i++)
    {
        int value = atoi(argv[i]);
        append(&list, value);
    }

    printf("Original list: ");
    print_list(&list);

    rearrange(&list);

    printf("Rearranged list: ");
    print_list(&list);

    return 0;
}