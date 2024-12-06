#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Global variables
int visited[MAX]; // Array to track visited vertices
int first[MAX];   // Array to store first visit time of each vertex
int last[MAX];    // Array to store last visit time of each vertex
int root[MAX];    // Array to store the root of the DFS tree
int Fcomp[MAX];   // Array to store which component a vertex belongs to
int parent[MAX];  // Array to store the parent of each vertex in the DFS forest
int fcomp = 0;    // Scalar for tracking the component number
int time = 0;     // Global time counter

// Function for DFS on a single vertex
void DFS_visit(int graph[MAX][MAX], int vertices, int v)
{
    visited[v] = 1;    // Mark vertex as visited
    Fcomp[v] = fcomp;  // Assign component number
    first[v] = ++time; // Record the start time

    for (int u = 0; u < vertices; u++)
    {
        if (graph[v][u] && !visited[u])
        {                  // Explore unvisited neighbors
            parent[u] = v; // Set parent of u to v
            DFS_visit(graph, vertices, u);
        }
    }
    last[v] = ++time; // Record the finish time
}

// Function for DFS over all vertices
void DFS(int graph[MAX][MAX], int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = 0; // Initialize visited array to 0
        parent[i] = -1; // Initialize parent array to -1
    }

    for (int v = 0; v < vertices; v++)
    {
        if (!visited[v])
        {                    // Start DFS on unvisited vertex
            fcomp++;         // Increment component count
            root[fcomp] = v; // Set root of the new tree
            DFS_visit(graph, vertices, v);
        }
    }
}

int main()
{
    int vertices;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix (use 0 for no edge and 1 for edge):\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    // Perform DFS
    DFS(graph, vertices);

    printf("\nVertex\tFirst\tLast\tParent\tComponent\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", i, first[i], last[i], parent[i], Fcomp[i]);
    }

    return 0;
}