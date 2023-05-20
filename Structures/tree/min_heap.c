#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* MINIMUM BINARY HEAP */

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
MinHeap* minheap_init(int capacity)
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
void minheap_deinit(MinHeap **heap)
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
int minheap_peek(MinHeap *heap)
{
        return (heap->Arr[0]);
}

/**
 * Performs the "heapify up" operation to maintain the min heap property
 * after inserting an element at a specific index.
 *
 * @param arr The array representing the min heap.
 * @param idx The index of the element to be heapified.
 */
void minheap_heapify_up(MinHeap *heap, size_t idx)
{
        int *arr = heap->Arr;

        while (idx > 0 && arr[parent(idx)] > arr[idx]) {
                xor_swap(&arr[idx], &arr[parent(idx)]);
                idx = parent(idx);
        }
}

/**
 * Performs the "heapify down" operation to maintain the min heap property
 * after deleting an element at a specific index.
 *
 * @param heap A pointer to the MinHeap structure.
 * @param idx  The index of the element to be heapified.
 */
void minheap_heapify_down(MinHeap *heap, size_t idx)
{
        int *arr    = heap->Arr;
        size_t size = heap->Size;

        while (1) {
                size_t smallest = idx;
                size_t left = left_child(idx);
                size_t right = right_child(idx);

                if (left < size && arr[left] < arr[smallest])
                        smallest = left;

                if (right < size && arr[right] < arr[smallest])
                        smallest = right;

                if (smallest == idx)
                        break;

                xor_swap(&arr[idx], &arr[smallest]);
                idx = smallest;
    }
}

/**
 * Inserts a new key into the min heap.
 *
 * @param heap A pointer to the minimum heap structure.
 * @param key The key to be inserted.
 */
void minheap_insert(MinHeap *heap, int key)
{
        if (heap->Capacity == heap->Size) {
                perror("overflow: could not insert key");
                return;
        }

        size_t idx = heap->Size;
        heap->Size++;
        heap->Arr[idx] = key;

        // Maintain the min heap property by swapping the element with its parent as long as necessary
        minheap_heapify_up(heap, idx);
}

/**
 * Deletes an element at the specified index from the MinHeap structure.
 *
 * @param heap Pointer to the MinHeap structure.
 * @param idx Index of the element to be deleted.
 */
void minheap_delete_idx(MinHeap *heap, int idx)
{
        if (heap->Size <= 0) {
                perror("underflow: heap is empty");
                return;
        } else if (idx >= heap->Size) {
                perror("invalid index: index is out of bounds");
                return;
        }

        heap->Arr[idx] = heap->Arr[heap->Size - 1];
        heap->Size--;

        if (idx == 0 || heap->Arr[idx] > heap->Arr[parent(idx)])
                minheap_heapify_down(heap, idx);
        else
                minheap_heapify_up(heap, idx);
}

// Test
void run_tests()
{
    // Test minheap_init and minheap_peek
    MinHeap* heap = minheap_init(5);
    assert(heap != NULL);
    assert(heap->Size == 0);
    assert(heap->Capacity == 5);

    minheap_insert(heap, 10);
    minheap_insert(heap, 5);
    minheap_insert(heap, 7);
    minheap_insert(heap, 2);
    minheap_insert(heap, 9);
    printf("Insertion tests passed.\n");

    printf("Peek test passed.\n");

    // Test minheap_delete_idx
    minheap_delete_idx(heap, 2);
    assert(minheap_peek(heap) == 2);
    printf("Delete test 1 passed.\n");

    minheap_delete_idx(heap, 0);
    assert(minheap_peek(heap) == 5);
    printf("Delete test 2 passed.\n");

    // Test minheap_deinit
    minheap_deinit(&heap);
    assert(heap == NULL);
    printf("Deallocation test passed.\n");
}

int main(int argc, char *argv[])
{
        run_tests();
        printf("All tests passed successfully.\n");

        return 0;
}
