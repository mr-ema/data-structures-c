#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
        struct Node *Left;
        struct Node *Right;
} Node;

typedef struct MinHeap {
        int *Arr;
        int Capacity;
        size_t Size;
} MinHeap;


/**
 * Swaps the values of two integer variables.
 *
 * @param a Pointer to the first integer variable.
 * @param b Pointer to the second integer variable.
 */
void xor_swap(int *a, int *b)
{
        if (*a == *b)
                return;

        *a ^= *b;
        *b ^= *a; 
        *a ^= *b;
}

/**
 * Returns the index of the parent node of the given index.
 *
 * @param index The index of the current node.
 * @return The index of the parent node.
 */
int parent(int index)
{
        return (index - 1) / 2;
}

/**
 * Returns the index of the left child node of the given index.
 *
 * @param index The index of the current node.
 * @return The index of the left child node.
 */
int left_child(int index)
{
        return (2 * index + 1);
}

/**
 * Returns the index of the right child node of the given index.
 *
 * @param index The index of the current node.
 * @return The index of the right child node.
 */
int right_child(int index)
{
        return (2 * index + 2);
}

/**
 * Initializes a new minimum heap with the given capacity.
 * If memory allocation fails, it exits the program with a status code of -1.
 *
 * @param capacity The maximum number of elements the heap can hold.
 * @return A pointer to the newly created heap.
 */
MinHeap* min_heap_init(int capacity)
{
        MinHeap *heap = malloc(sizeof(MinHeap));
        if (!heap) {
                perror("error: memory allocation failed");
                exit(-1);
        }

        heap->Arr = (int*)malloc(capacity * sizeof(int));
        if (!(heap->Arr)) {
                perror("error: memory allocation failed");
                free(heap);
                exit(-1);
        }

        heap->Size      = 0;
        heap->Capacity  = capacity;

        return heap;
}

/**
 * Deallocates the memory used by a min heap.
 *
 * @param heap A pointer to the pointer of the min heap to be deallocated.
 */
void min_heap_deinit(MinHeap **heap)
{
        free((*heap)->Arr);     // Free the memory for the array
        free(*heap);            // Free the memory for the MinHeap struct

        *heap = NULL;           // Set the heap pointer to NULL
}

/**
 * Returns the minimum key on a min heap.
 *
 * @param heap A pointer to the min heap structure.
 * @return The minimum key in the min heap.
 */
int min_heap_get_min(MinHeap *heap)
{
        return (heap->Arr[0]);
}

/**
 * Performs the heapify operation on a min heap represented as an array.
 *
 * @param arr The array representing the min heap.
 * @param idx The index of the current node to heapify.
 */
void min_heap_heapify(int* arr, size_t idx)
{
        while (idx > 0 && arr[parent(idx)] > arr[idx]) {
                xor_swap(&(arr[idx]), &(arr[parent(idx)]));
                idx = parent(idx);
        }
}

/**
 * Inserts a new key into the min heap.
 *
 * @param heap A pointer to the minimum heap structure.
 * @param key The key to be inserted.
 */
void min_heap_insert(MinHeap *heap, int key)
{
        if (heap->Capacity == heap->Size) {
                perror("overflow: could not insert key");
                return;
        }

        size_t idx = heap->Size;
        heap->Size++;
        heap->Arr[idx] = key;

        // Maintain the min heap property by swapping the element with its parent as long as necessary
        while (idx > 0 && heap->Arr[parent(idx)] > heap->Arr[idx]) {
                xor_swap(&(heap->Arr[idx]), &(heap->Arr[parent(idx)]));
                idx = parent(idx);
        }
}

void min_heap_delete(MinHeap *heap, int key) {}

void min_heap_peek(MinHeap *heap) {}
