
/*
    When recursion happens, the stack space is occupied. The system keeps a track of the pcb of each function so the chunk of memory assigned to each fn call is quite high.
    If we somehow take care of this extra information stored in our own stack, the memory assigned to each fn call will be quite less so we can reduce the chances of stack overflow.
    To demonstrate, we write a iterative version of pre-order.

    If this were preorder, we simply print the vertex and forget it, ie not store on stack, we just remember the left and right subtree.
    Here however, I cant ignore it because I need to come back to it again, we visit every node thrice.
    So on my custom stack, I keep track of the node and the number of times I've visited it.
    Each element is: {root fo subtree not yet completed, "state": no of visits made to this root}
    Instead of using the system's stack, we use our own stack to do this.
*/
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10
#define NEW 1
#define LEFT_DONE 2
#define RIGHT_DONE 3

typedef int DATA;

typedef struct tnode
{
    DATA d;
    int left, right;
    int parent;
} TNODE;

typedef struct
{
    int capacity, num_nodes, root;
    TNODE *node_list; // Array following the alternative implementation
} TREE;

typedef struct
{
    int root, state;
} PAIR;

typedef struct
{
    PAIR stack[CAPACITY];
    int top;
} STACK;

// Stack utility functions
void init_stack(STACK *S)
{
    S->top = -1;
}

int push(STACK *S, int root, int state)
{
    if (S->top == CAPACITY - 1)
        return -1;
    S->top++;
    S->stack[S->top].root = root;
    S->stack[S->top].state = state;
    return 0;
}

int pop(STACK *S, PAIR *X)
{
    if (S->top == -1)
        return -1;
    *X = S->stack[S->top];
    S->top--;
    return 0;
}

// Pre-order traversal (root, left, right)
void preorder(TREE *t, int root)
{
    if (root == -1)
        return;

    STACK S;
    PAIR X;
    init_stack(&S);
    push(&S, root, NEW);

    while (S.top != -1)
    {
        pop(&S, &X);
        if (X.state != -1)
        {
            switch (X.state)
            {
            case NEW:
                printf("%d ", t->node_list[X.root].d);
                push(&S, X.root, LEFT_DONE);
                if (t->node_list[X.root].left != -1)
                {
                    push(&S, t->node_list[X.root].left, NEW);
                }
                break;

            case LEFT_DONE:
                push(&S, X.root, RIGHT_DONE);
                if (t->node_list[X.root].right != -1)
                {
                    push(&S, t->node_list[X.root].right, NEW);
                }
                break;
            }
        }
    }
}

// In-order traversal (left, root, right)
void inorder(TREE *t, int root)
{
    if (root == -1)
        return;

    STACK S;
    PAIR X;
    init_stack(&S);
    push(&S, root, NEW);

    while (S.top != -1)
    {
        pop(&S, &X);
        if (X.state != -1)
        {
            switch (X.state)
            {
            case NEW:
                push(&S, X.root, LEFT_DONE);
                if (t->node_list[X.root].left != -1)
                {
                    push(&S, t->node_list[X.root].left, NEW);
                }
                break;

            case LEFT_DONE:
                printf("%d ", t->node_list[X.root].d);
                push(&S, X.root, RIGHT_DONE);
                if (t->node_list[X.root].right != -1)
                {
                    push(&S, t->node_list[X.root].right, NEW);
                }
                break;
            }
        }
    }
}

// Post-order traversal (left, right, root)
void postorder(TREE *t, int root)
{
    if (root == -1)
        return;

    /*
    Recursive Approach: 3 ops per node - visit first, explore left and come back, explore right and come back, finally print it. This op seq is repeated for every node.
    postorder(t, tree->node_list[root].left);
    postorder(t, tree->node_list[root].right);
    printf("%d", t->node_list[root].d);
    return;
    */

    STACK S;
    PAIR X;
    init_stack(&S);
    push(&S, root, NEW);

    while (S.top != -1)
    {
        pop(&S, &X);
        if (X.state != -1)
        {
            switch (X.state)
            {
            case NEW:
                push(&S, X.root, LEFT_DONE);
                if (t->node_list[X.root].left != -1)
                {
                    push(&S, t->node_list[X.root].left, NEW);
                }
                break;

            case LEFT_DONE:
                push(&S, X.root, RIGHT_DONE);
                if (t->node_list[X.root].right != -1)
                {
                    push(&S, t->node_list[X.root].right, NEW);
                }
                break;

            case RIGHT_DONE:
                printf("%d ", t->node_list[X.root].d);
                break;
            }
        }
    }
}

// Helper to create a sample binary tree
TREE *create_tree()
{
    TREE *t = (TREE *)malloc(sizeof(TREE));
    t->capacity = CAPACITY;
    t->num_nodes = 5;
    t->root = 0;
    t->node_list = (TNODE *)malloc(t->capacity * sizeof(TNODE));

    t->node_list[0] = (TNODE){1, 1, 2, -1};
    t->node_list[1] = (TNODE){2, 3, 4, 0};
    t->node_list[2] = (TNODE){3, -1, -1, 0};
    t->node_list[3] = (TNODE){4, -1, -1, 1};
    t->node_list[4] = (TNODE){5, -1, -1, 1};

    return t;
}

int main()
{
    TREE *tree = create_tree();

    printf("Pre-order Traversal: ");
    preorder(tree, tree->root);
    printf("\n");

    printf("In-order Traversal: ");
    inorder(tree, tree->root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorder(tree, tree->root);
    printf("\n");

    free(tree->node_list);
    free(tree);

    return 0;
}