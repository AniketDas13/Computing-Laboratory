#include "generic_ll.h"

// Initialize the linked list
void init_list(LINKEDLIST *list, size_t data_size) {
    list->head = NULL;
    list->data_size = data_size;
}

// Insert a new element at the end of the list
void insert_end(LINKEDLIST *list, void *data) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        NODE *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Insert a new element in sorted order
void insert_sorted(LINKEDLIST *list, void *data, int (*compare)(const void *, const void *)) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->data = malloc(list->data_size);
    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;

    if (list->head == NULL || compare(data, list->head->data) < 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        NODE *current = list->head;
        while (current->next != NULL && compare(data, current->next->data) > 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Display the linked list
void display_list(LINKEDLIST *list, void (*print_data)(const void *)) {
    NODE *current = list->head;
    while (current != NULL) {
        print_data(current->data);
        current = current->next;
    }
    printf("\n");
}

// Free the linked list memory
void free_list(LINKEDLIST *list) {
    NODE *current = list->head;
    while (current != NULL) {
        NODE *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    list->head = NULL;
}
