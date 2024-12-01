#include <stdio.h>
#include <stdlib.h>

// Define the node structure for linked list
typedef struct _node
{
    int data;           // Value stored in each node
    struct _node *next; // Pointer to the next node
} node;

// Function to create and initialize a new node with given data
node *create_node(int data)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        printf("Memory allocation error\n");
        exit(1); // Exit if memory allocation fails
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Function to generate the sequence list based on the modulus M and initial value x0
node *genrho(int M, int x0)
{
    node *head = create_node(x0); // Initialize the list with the starting value x0
    node *current = head;         // Pointer to keep track of the last node added
    // node *slow = head;            // Slow pointer for cycle detection
    // node *fast = head;            // Fast pointer for cycle detection

    printf("%d: Inserted... continuing...\n", x0); // Output for the first node

    // Generate sequence and add nodes until a cycle is detected
    while (1)
    {
        // Calculate the next value in the sequence
        x0 = (x0 * x0 + 1) % M;

        // Check if the new value already exists by traversing from head to current
        node *temp = head;
        while (temp != current->next)
        {
            if (temp->data == x0)
            {
                printf("%d: Cycle detected... breaking...\n", x0);
                current->next = temp; // Link the last node to the node where the cycle starts
                return head;          // Return the head of the list with a cycle
            }
            temp = temp->next;
        }

        // Create and link the new node if no cycle is detected
        node *new_node = create_node(x0);
        current->next = new_node;
        current = new_node;

        // Output each inserted node
        printf("%d: Inserted... continuing...\n", x0);
    }

    return head; // Return the head of the list
}

// Function to calculate the length of the detected cycle in the list
int cyclelen(node *head)
{
    node *slow = head, *fast = head;

    // Use Floyd's Tortoise and Hare algorithm to locate cycle
    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;       // Move slow pointer by one step
        fast = fast->next->next; // Move fast pointer by two steps
        if (slow == fast)
        { // Cycle detected
            int length = 0;
            do
            {
                slow = slow->next;
                length++;
            } while (slow != fast); // Loop until the cycle completes

            return length; // Return cycle length
        }
    }

    return 0; // Return 0 if no cycle is found (should not occur per problem)
}

// Wrapper function to generate the list using genrho
node *genList(int M, int x0)
{
    return genrho(M, x0);
}

// Function to free the memory of the linked list
// void free_list(node *head)
// {
//     node *temp;
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
// }

int main()
{
    int M, x0;

    // Test cases provided in the question
    int test_cases[4][2] = {{50, 11}, {100, 5}, {6543, 3456}, {35791, 13579}};

    for (int i = 0; i < 4; i++)
    {
        M = test_cases[i][0];
        x0 = test_cases[i][1];

        printf("Generating sequence for M = %d, x0 = %d\n", M, x0);

        // Generate the sequence list and detect cycle
        node *head = genList(M, x0); // Calls genList which in turn calls genrho

        // Calculate the cycle length
        int cycle_length = cyclelen(head);
        printf("Cycle length for M = %d, x0 = %d is: %d\n\n", M, x0, cycle_length);

        // Free the allocated list memory
        // free_list(head);
    }

    return 0;
}