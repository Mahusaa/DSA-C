#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1

// Structure to represent a binary heap
typedef struct {
    int size;        // Current number of elements in the heap
    int capacity;    // Total capacity of the heap
    int* heap;       // Pointer to the dynamically allocated array storing the heap elements
} BinaryHeap;

// Function to create a new binary heap
BinaryHeap* createBinaryHeap() {
    // Allocate memory for the BinaryHeap structure
    BinaryHeap* heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    // Initialize size to 0, capacity to INITIAL_CAPACITY, and allocate memory for the heap array
    heap->size = 0;
    heap->capacity = INITIAL_CAPACITY;
    heap->heap = (int*)malloc(heap->capacity * sizeof(int));
    return heap;
}

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to move an element up in the heap (used when adding elements)
void swim(BinaryHeap* heap, int k) {
    while (k > 0 && heap->heap[k] < heap->heap[(k - 1) / 2]) {
        // Swap with the parent until the heap property is satisfied
        swap(&heap->heap[k], &heap->heap[(k - 1) / 2]);
        k = (k - 1) / 2;  // Move to the parent index
    }
}

// Function to move an element down in the heap (used when removing elements)
void sink(BinaryHeap* heap, int k) {
    int left, right, smallest;
    while (1) {
        left = 2 * k + 1;
        right = 2 * k + 2;
        smallest = left;

        // Determine the index of the smallest child (left or right)
        if (right < heap->size && heap->heap[right] < heap->heap[left]) {
            smallest = right;
        }

        // Break if the heap property is satisfied or if we reach the end of the heap
        if (left >= heap->size || heap->heap[k] < heap->heap[smallest]) {
            break;
        }

        // Swap with the smallest child and continue the sinking process
        swap(&heap->heap[k], &heap->heap[smallest]);
        k = smallest;
    }
}

// Function to add an element to the binary heap
void add(BinaryHeap* heap, int elem) {
    // Check if the heap is full and resize if necessary
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->heap = (int*)realloc(heap->heap, heap->capacity * sizeof(int));
    }

    // Add the new element to the end of the heap
    heap->heap[heap->size] = elem;
    // Move the element up to its correct position to maintain the heap property
    swim(heap, heap->size);
    // Increment the size of the heap
    heap->size++;
}

// Function to remove and return the minimum element from the binary heap
int poll(BinaryHeap* heap) {
    if (heap->size == 0) {
        // Handle empty heap
        return -1; // Assuming -1 represents an invalid value
    }

    // Store the root (minimum) element
    int root = heap->heap[0];
    // Replace the root with the last element in the heap
    heap->heap[0] = heap->heap[heap->size - 1];
    // Decrement the size of the heap
    heap->size--;
    // Move the new root down to its correct position to maintain the heap property
    sink(heap, 0);

    // Return the minimum element that was removed
    return root;
}

// Function to print the elements of the binary heap
void printHeap(BinaryHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->heap[i]);
    }
    printf("\n");
}

int removeElement(BinaryHeap* heap, int elem) {
    int index;
    for (index = 0; index < heap->size; index++) {
        if (heap->heap[index] == elem) {
            break;
        }
    }

    if (index == heap->size) {
        // Element not found
        return -1;
    }

    int removedValue = heap->heap[index];
    heap->heap[index] = heap->heap[heap->size - 1];
    heap->size--;
    sink(heap, index);
    swim(heap, index);

    return removedValue;
}

// Main function for testing the binary heap with remove operation
int main() {
    // Create a new binary heap
    BinaryHeap* heap = createBinaryHeap();

    // Testing the binary heap
    add(heap, 3);
    add(heap, 1);
    add(heap, 4);
    add(heap, 1);
    add(heap, 5);

    // Print the current state of the heap
    printf("Min Heap: ");
    printHeap(heap);

    // Remove the minimum element and print the updated heap
    int min = poll(heap);
    printf("Min Element Removed: %d\n", min);
    printf("Min Heap after removal: ");
    printHeap(heap);

    // Remove a specific element (e.g., 4) and print the updated heap
    int removedElem = removeElement(heap, 4);
    if (removedElem != -1) {
        printf("Element 4 Removed: %d\n", removedElem);
        printf("Heap after removing element 4: ");
        printHeap(heap);
    } else {
        printf("Element 4 not found in the heap.\n");
    }

    // Don't forget to free the allocated memory
    free(heap->heap);
    free(heap);

    return 0;
}
