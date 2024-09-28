#include <stdio.h>
#include <stdlib.h>

// Function to rotate a specific layer
void rotateLayer(int **matrix, int m, int n, int layer, char direction, int positions)
{
    int temp[100]; // Array to hold the layer elements temporarily
    int idx = 0;

    // Extract the layer into temp array
    for (int i = layer; i < n - layer; i++)
        temp[idx++] = matrix[layer][i];
    for (int i = layer + 1; i < m - layer; i++)
        temp[idx++] = matrix[i][n - layer - 1];
    for (int i = n - layer - 2; i >= layer; i--)
        temp[idx++] = matrix[m - layer - 1][i];
    for (int i = m - layer - 2; i > layer; i--)
        temp[idx++] = matrix[i][layer];

    int totalElements = idx;
    positions = positions % totalElements; // Handle overflow

    // Rotate the layer
    int rotated[100];
    for (int i = 0; i < totalElements; i++)
    {
        if (direction == 'C')
        {
            rotated[(i + positions) % totalElements] = temp[i];
        }
        else
        {
            rotated[(i - positions + totalElements) % totalElements] = temp[i];
        }
    }

    // Put back rotated elements into the matrix
    idx = 0;
    for (int i = layer; i < n - layer; i++)
        matrix[layer][i] = rotated[idx++];
    for (int i = layer + 1; i < m - layer; i++)
        matrix[i][n - layer - 1] = rotated[idx++];
    for (int i = n - layer - 2; i >= layer; i--)
        matrix[m - layer - 1][i] = rotated[idx++];
    for (int i = m - layer - 2; i > layer; i--)
        matrix[i][layer] = rotated[idx++];
}

int main()
{
    int m, n, layer, positions;
    char direction;

    // Read matrix dimensions
    scanf("%d %d", &m, &n);

    // Dynamically allocate memory for the matrix
    int **matrix = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Read matrix elements
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Read the rotation direction, number of positions, and the layer
    // Space before %c is intentional and tells scanf to skip any whitespace before reading the character
    scanf(" %c %d %d", &direction, &positions, &layer);

    // Perform the layerwise rotation
    rotateLayer(matrix, m, n, layer - 1, direction, positions); // layer-1 to convert to 0-indexed

    // Print the rotated matrix
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}