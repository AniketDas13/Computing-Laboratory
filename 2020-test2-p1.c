#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int x, y;           // Interval [x, y] of the node
    int left, right;    // Indices of the left and right children (-1 if absent)
    int span_x, span_y; // Span of the subtree rooted at this node
} Node;

void computeSpans(Node nodes[], int index)
{
    if (index == -1)
        return;

    Node *current = &nodes[index];

    // Compute spans for left and right subtrees
    computeSpans(nodes, current->left);
    computeSpans(nodes, current->right);

    // Start with the interval of the current node
    current->span_x = current->x;
    current->span_y = current->y;

    // Update span with left subtree
    if (current->left != -1)
    {
        current->span_x = (current->span_x < nodes[current->left].span_x)
                              ? current->span_x
                              : nodes[current->left].span_x;
        current->span_y = (current->span_y > nodes[current->left].span_y)
                              ? current->span_y
                              : nodes[current->left].span_y;
    }

    // Update span with right subtree
    if (current->right != -1)
    {
        current->span_x = (current->span_x < nodes[current->right].span_x)
                              ? current->span_x
                              : nodes[current->right].span_x;
        current->span_y = (current->span_y > nodes[current->right].span_y)
                              ? current->span_y
                              : nodes[current->right].span_y;
    }
}

int findMaxIntersection(Node nodes[], int index, int *cutIndex, int *maxIntersection)
{
    if (index == -1)
        return 0;

    Node *current = &nodes[index];
    int leftSpan = findMaxIntersection(nodes, current->left, cutIndex, maxIntersection);
    int rightSpan = findMaxIntersection(nodes, current->right, cutIndex, maxIntersection);

    // Compute intersection for current node's children
    if (current->left != -1 && current->right != -1)
    {
        int intersectionStart = (nodes[current->left].span_x > nodes[current->right].span_x)
                                    ? nodes[current->left].span_x
                                    : nodes[current->right].span_x;
        int intersectionEnd = (nodes[current->left].span_y < nodes[current->right].span_y)
                                  ? nodes[current->left].span_y
                                  : nodes[current->right].span_y;

        int intersectionSize = (intersectionEnd >= intersectionStart) ? (intersectionEnd - intersectionStart + 1) : 0;

        if (intersectionSize > *maxIntersection)
        {
            *maxIntersection = intersectionSize;
            *cutIndex = index;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char mode = argv[1][0]; // Command-line argument 'a' or 'b'

    int n;
    scanf("%d", &n);

    Node nodes[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &nodes[i].x, &nodes[i].y, &nodes[i].left, &nodes[i].right);
        nodes[i].span_x = nodes[i].span_y = -1; // Initialize spans
    }

    // Compute spans for all nodes
    computeSpans(nodes, 0);

    if (mode == 'a')
    {
        // Output spans for part (a)
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
        {
            printf("%d %d %d %d\n", nodes[i].span_x, nodes[i].span_y, nodes[i].left, nodes[i].right);
        }
    }
    else if (mode == 'b')
    {
        // Find the edge to cut for part (b)
        int cutIndex = -1, maxIntersection = 0;
        findMaxIntersection(nodes, 0, &cutIndex, &maxIntersection);
        printf("%d\n", cutIndex);
    }

    return 0;
}