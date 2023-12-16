#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure
typedef struct Stack {
    Node* top;
} Stack;

// Function to initialize an empty stack
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, int data) {
    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Set the data and update the next pointer
    newNode->data = data;
    newNode->next = stack->top;

    // Update the top pointer to the new node
    stack->top = newNode;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }

    // Get the data from the top node
    int data = stack->top->data;

    // Update the top pointer to the next node
    Node* temp = stack->top;
    stack->top = stack->top->next;

    // Free the memory of the popped node
    free(temp);

    return data;
}

// Function to print the elements of the stack
void printStack(Stack* stack) {
    Node* current = stack->top;
    printf("Stack: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the stack
void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}

int main() {
    Stack myStack;
    initializeStack(&myStack);

    push(&myStack, 1);
    push(&myStack, 2);
    push(&myStack, 3);

    printStack(&myStack);

    printf("Popped element: %d\n", pop(&myStack));

    printStack(&myStack);

    // Free the memory allocated for the stack
    freeStack(&myStack);

    return 0;
}

