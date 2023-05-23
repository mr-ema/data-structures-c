#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* MAX-HEAP DATA STRUCTURE */
typedef struct MaxHeap {
        int *Arr;
        int Capacity;
        size_t Size;
} MaxHeap;


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
 * Initializes a Max Heap with the specified capacity.
 *
 * @param capacity The maximum number of elements the heap can hold.
 * @return A pointer to the initialized MaxHeap struct.
 *         Exits the program if memory allocation fails.
 */
MaxHeap* maxheap_init(int capacity)
{
        MaxHeap *heap = malloc(sizeof(MaxHeap));
        if (!heap) {
                fprintf(stderr, "error: memory allocation failed");
                exit(-1);
        }

        heap->Arr = (int*)malloc(capacity * sizeof(int));
        if (!(heap->Arr)) {
                fprintf(stderr, "error: memory allocation failed");

                free(heap); // free previous allocated memory
                exit(-1);
        }

        heap->Size      = 0;
        heap->Capacity  = capacity;

        return heap;
}

/**
 * Deinitializes a Max Heap and frees the allocated memory.
 *
 * @param heap A double pointer to the MaxHeap struct.
 *             The pointer will be set to NULL after memory deallocation.
 */
void maxheap_deinit(MaxHeap **heap)
{
        free((*heap)->Arr);     // Free the memory for the array
        free(*heap);            // Free the memory for the MaxHeap struct

        *heap = NULL;           // Set the heap pointer to NULL
}

/**
 * Retrieves the maximum element from the Max Heap without removing it.
 *
 * @param heap A pointer to the MaxHeap struct.
 * @return The maximum element in the Max Heap.
 */
int maxheap_peek(MaxHeap *heap)
{
        return (heap->Arr[0]);
}

/**
 * Restores the Max Heap property by moving the element at the given index up to its correct position.
 *
 * @param heap A pointer to the MaxHeap struct.
 * @param idx The index of the element to be heapified up.
 */
void maxheap_heapify_up(MaxHeap *heap, size_t idx)
{
        int *arr = heap->Arr;

        while (idx > 0 && arr[idx] > arr[parent(idx)]) {
                xor_swap(&arr[idx], &arr[parent(idx)]);
                idx = parent(idx);
        }
}

/**
 * Restores the Max Heap property by moving the element at the given index down to its correct position.
 *
 * @param heap A pointer to the MaxHeap struct.
 * @param idx The index of the element to be heapified down.
 */
void maxheap_heapify_down(MaxHeap *heap, size_t idx)
{
        int *arr    = heap->Arr;
        size_t size = heap->Size;

        while (1) {
                size_t bigger   = idx;
                size_t left     = left_child(idx);
                size_t right    = right_child(idx);

                if (left < size && arr[left] > arr[bigger])
                        bigger = left;

                if (right < size && arr[right] > arr[bigger])
                        bigger = right;

                if (bigger == idx)
                        break;

                xor_swap(&arr[idx], &arr[bigger]);
                idx = bigger;
        }
}

/**
 * Inserts a new key into the Max Heap.
 *
 * @param heap A pointer to the MaxHeap struct.
 * @param key The key to be inserted into the Max Heap.
 */
void maxheap_insert(MaxHeap *heap, int key)
{
        if (heap->Capacity == heap->Size) {
                fprintf(stderr, "overflow: could not insert key");
                return;
        }

        size_t idx = heap->Size;
        heap->Size++;
        heap->Arr[idx] = key;

        // Maintain the max-heap property by swapping the element with its parent as long as necessary
        maxheap_heapify_up(heap, idx);
}

/**
 * Deletes the element at the specified index from the Max Heap.
 *
 * @param heap A pointer to the MaxHeap struct.
 * @param idx The index of the element to be deleted.
 */
void maxheap_delete_idx(MaxHeap *heap, int idx)
{
        if (heap->Size <= 0) {
                fprintf(stderr, "underflow: heap is empty");
                return;
        } else if (idx >= heap->Size) {
                fprintf(stderr, "invalid index: index is out of bounds");
                return;
        }

        // Swap the key at the given index with the last key in the heap
        heap->Arr[idx] = heap->Arr[heap->Size - 1];
        heap->Size--; // Decrease the size of the heap to remove the last key (key to be deleted)

        if (heap->Arr[idx] > heap->Arr[parent(idx)])
                maxheap_heapify_up(heap, idx);
        else
                maxheap_heapify_down(heap, idx);
}

// Test
int main()
{
        MaxHeap* heap = maxheap_init(10);

        // Test inserting elements
        maxheap_insert(heap, 5);
        maxheap_insert(heap, 3);
        maxheap_insert(heap, 8);
        maxheap_insert(heap, 2);
        maxheap_insert(heap, 9);
        assert(maxheap_peek(heap) == 9);

        // Test deleting elements
        maxheap_delete_idx(heap, 1); // Delete element at index 1 (value 8)
        assert(maxheap_peek(heap) == 9);

        maxheap_delete_idx(heap, 0); // Delete element at index 0 (value 9)
        assert(maxheap_peek(heap) == 5);

        // Test inserting more elements
        maxheap_insert(heap, 12);
        maxheap_insert(heap, 6);
        maxheap_insert(heap, 10);
        assert(maxheap_peek(heap) == 12);

        // Test deleting elements
        maxheap_delete_idx(heap, 2); // Delete element at index 2 (value 10)
        assert(maxheap_peek(heap) == 12);

        maxheap_delete_idx(heap, 0); // Delete element at index 0 (value 12)
        assert(maxheap_peek(heap) == 6);

        // Test inserting elements in descending order
        maxheap_insert(heap, 9);
        maxheap_insert(heap, 8);
        maxheap_insert(heap, 7);
        maxheap_insert(heap, 6);
        maxheap_insert(heap, 5);

        // Test deleting all elements
        while (heap->Size > 0) {
                maxheap_delete_idx(heap, 0);
        }
        assert(heap->Size == 0);

        maxheap_deinit(&heap);

        return 0;
}
