#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Queue structure for BFS
typedef struct Queue
{
    int items[MAX];
    int front, rear;
} Queue;

// Function to create a queue
Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(Queue *q)
{
    return q->front == -1;
}

// Enqueue an element to the queue
void enqueue(Queue *q, int value)
{
    if (q->rear == MAX - 1)
        return; // Queue overflow
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

// Dequeue an element from the queue
int dequeue(Queue *q)
{
    if (isEmpty(q))
        return -1; // Queue underflow
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
        q->front = q->rear = -1;
    return item;
}

// Function to perform BFS
void BFS(int graph[MAX][MAX], int vertices, int start)
{
    int dist[MAX], parent[MAX];
    Queue *q = createQueue();

    // Initialize distances and parents
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX; // Equivalent to ∞
        parent[i] = -1;    // Equivalent to ⊥
    }
    dist[start] = 0;

    // Enqueue the start vertex
    enqueue(q, start);

    // BFS loop
    while (!isEmpty(q))
    {
        int v = dequeue(q);
        for (int u = 0; u < vertices; u++)
        {
            // Check if there's an edge and if u's dist is too large
            if (graph[v][u] && dist[u] > dist[v] + 1)
            {
                dist[u] = dist[v] + 1;
                parent[u] = v;
                enqueue(q, u);
            }
        }
    }

    // Print distances and parents
    printf("Vertex\tDistance\tParent\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d\t%d\t\t%d\n", i, dist[i], parent[i]);
    }

    // Free the queue
    free(q);
}

int main()
{
    int vertices, start;
    int graph[MAX][MAX] = {0};

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start);

    // Perform BFS
    BFS(graph, vertices, start);

    return 0;
}