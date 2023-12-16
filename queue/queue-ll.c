#include <stdio.h>
#include <stdlib.h>

//FRONT IS LEFT, REAR IS RIGHT


// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct LinkedQueue {
    Node* front; // Front of the queue
    Node* rear;  // Rear of the queue
} LinkedQueue;

// Function to initialize an empty queue
void initializeQueue(LinkedQueue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(LinkedQueue* queue) {
    return queue->front == NULL;
}

// Function to peek the element at the front of the queue
// Get data in front
int peek(LinkedQueue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue Empty\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->data;
}

// Function to poll an element from the front of the queue
// remove front element(dequeuing)
int poll(LinkedQueue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue Empty\n");
        exit(EXIT_FAILURE);
    }

    // Get the data from the front node
    int data = queue->front->data;

    // Update the front pointer to the next node
    Node* temp = queue->front;
    queue->front = queue->front->next;

    // Free the memory of the front node
    free(temp);

    // If the queue becomes empty, update the rear pointer to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return data;
}

// Function to offer an element to the back of the queue
// Add element to rear(enqueing)
void offer(LinkedQueue* queue, int elem) {
    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Set the data and update the next pointer
    newNode->data = elem;
    newNode->next = NULL;

    // If the queue is empty, update both front and rear pointers
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        // Update the rear pointer to the new node
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to free the memory allocated for the queue
void freeQueue(LinkedQueue* queue) {
    while (!isEmpty(queue)) {
        poll(queue);
    }
}

int main() {
    LinkedQueue myQueue;
    initializeQueue(&myQueue);

    offer(&myQueue, 1);
    offer(&myQueue, 2);
    offer(&myQueue, 3);

    printf("Front element: %d\n", peek(&myQueue));

    printf("Polled element: %d\n", poll(&myQueue));
    printf("Polled element: %d\n", poll(&myQueue));

    freeQueue(&myQueue);

    return 0;
}

