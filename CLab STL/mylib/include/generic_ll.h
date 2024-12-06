#ifndef GENERIC_LINKEDLIST_H
#define GENERIC_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for the linked list
typedef struct node {
    void *data;       // Generic pointer for data
    struct node *next; // Pointer to the next node
} NODE;

// Linked list structure
typedef struct {
    NODE *head;          // Pointer to the head node
    size_t data_size;    // Size of the data type
} LINKEDLIST;

// Function prototypes
void init_list(LINKEDLIST *list, size_t data_size);
void insert_end(LINKEDLIST *list, void *data);
void insert_sorted(LINKEDLIST *list, void *data, int (*compare)(const void *, const void *));
void display_list(LINKEDLIST *list, void (*print_data)(const void *));
void free_list(LINKEDLIST *list);

#endif // GENERIC_LINKEDLIST_H
