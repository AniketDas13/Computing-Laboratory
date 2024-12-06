#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

// Function to find the vertex with minimum distance not in the set R
int minDistance(int dist[], bool R[], int vertices)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
    {
        if (!R[v] && dist[v] < min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to implement Dijkstra's algorithm
void Dijkstra(int graph[MAX][MAX], int vertices, int start)
{
    int dist[MAX];   // Distance labels
    int parent[MAX]; // Parent vertices
    bool R[MAX];     // Set of reached vertices

    // Initialization
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX; // Equivalent to ∞
        parent[i] = -1;    // Equivalent to ⊥
        R[i] = false;      // None of the vertices are in R initially
    }
    dist[start] = 0;

    // Dijkstra's Algorithm
    for (int count = 0; count < vertices - 1; count++)
    {
        // Choose the vertex with the smallest distance not in R
        int v = minDistance(dist, R, vertices);

        // If the smallest distance is infinity, break
        if (dist[v] == INT_MAX)
            break;

        // Add v to the set R
        R[v] = true;

        // Update distance value of the adjacent vertices of the chosen vertex
        for (int u = 0; u < vertices; u++)
        {
            // Update dist[u] only if u is not in R, there is an edge from v to u,
            // and the total weight of path from start to u through v is smaller
            if (!R[u] && graph[v][u] && dist[v] != INT_MAX && dist[v] + graph[v][u] < dist[u])
            {
                dist[u] = dist[v] + graph[v][u];
                parent[u] = v;
            }
        }
    }

    // Print distances and parents
    printf("Vertex\tDistance\tParent\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d\t%d\t\t%d\n", i, dist[i], parent[i]);
    }
}

int main()
{
    int vertices, start;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix (use 0 for no direct path):\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start);

    // Perform Dijkstra's algorithm
    Dijkstra(graph, vertices, start);

    return 0;
}