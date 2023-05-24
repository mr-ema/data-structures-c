#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct MaxHeap {
        int *data;
        size_t capacity;
        size_t len;
} MaxHeap;


void xor_swap(int *a, int *b) {
        if (*a == *b)
                return;

        *a ^= *b;
        *b ^= *a; 
        *a ^= *b;
}

int parent_idx(int index) {
        return ((index - 1) / 2);
}

int left_child_idx(int index) {
        return (2 * index + 1);
}

int right_child_idx(int index) {
        return (2 * index + 2);
}

MaxHeap* maxheap_init(size_t capacity) {
        MaxHeap *heap = malloc(sizeof(MaxHeap));
        if (!heap) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        heap->data = (int*)malloc(capacity * sizeof(int));
        if (!(heap->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(heap); // free previous allocated memory
                exit(-1);
        }

        heap->len       = 0;
        heap->capacity  = capacity;

        return heap;
}

void maxheap_deinit(MaxHeap **self) {
        free((*self)->data); // Free the memory for the array
        free(*self); // Free the memory for the MaxHeap struct

        *self = NULL; // Remove the pointer reference to the heap
}

size_t maxheap_len(const MaxHeap *self) {
        return self->len;
}

int maxheap_is_empty(const MaxHeap *self) {
        return (self->len <= 0);
}

int maxheap_peek(const MaxHeap *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: heap is empty!\n");
                return -1;
        }

        return (self->data[0]);
}

void maxheap_heapify_up(MaxHeap *self, size_t idx) {
        int *heap = self->data;

        while (idx > 0 && heap[idx] > heap[parent_idx(idx)]) {
                xor_swap(&heap[idx], &heap[parent_idx(idx)]);
                idx = parent_idx(idx);
        }
}

void maxheap_heapify_down(MaxHeap *self, size_t idx) {
        int *heap = self->data;
        size_t len = self->len;

        while (1) {
                size_t bigger = idx;
                size_t left   = left_child_idx(idx);
                size_t right  = right_child_idx(idx);

                if (left < len && heap[left] > heap[bigger])
                        bigger = left;

                if (right < len && heap[right] > heap[bigger])
                        bigger = right;

                if (bigger == idx)
                        break;

                xor_swap(&heap[idx], &heap[bigger]);
                idx = bigger;
        }
}

void maxheap_insert(MaxHeap *self, int key) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "overflow: could not insert key!\n");
                return;
        }

        size_t idx = self->len;
        self->len++;
        self->data[idx] = key;

        // Maintain the max-heap property by swapping the element with its parent as long as necessary
        maxheap_heapify_up(self, idx);
}

void maxheap_delete(MaxHeap *self, int idx) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to delete, the heap is empty!\n");
                return;
        } else if (idx >= self->len) {
                fprintf(stderr, "invalid index: index is out of bounds!\n");
                return;
        }

        // Swap the key at the given index with the last key in the heap
        self->data[idx] = self->data[self->len - 1];
        self->len--; // Decrease the size of the heap to remove the last key (key to be deleted)

        if (self->data[idx] > self->data[parent_idx(idx)])
                maxheap_heapify_up(self, idx);
        else
                maxheap_heapify_down(self, idx);
}

// Test
int main() {
        MaxHeap* heap = maxheap_init(10);

        // Test inserting elements
        maxheap_insert(heap, 5);
        maxheap_insert(heap, 3);
        maxheap_insert(heap, 8);
        maxheap_insert(heap, 2);
        maxheap_insert(heap, 9);

        if (maxheap_peek(heap) == 9)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 5)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        // Test deleting elements
        maxheap_delete(heap, 1); // Delete element at index 1 (value 8)

        if (maxheap_peek(heap) == 9)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 4)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        maxheap_delete(heap, 0); // Delete element at index 0 (value 9)

        if (maxheap_peek(heap) == 5)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 3)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        // Test inserting more elements
        maxheap_insert(heap, 12);
        maxheap_insert(heap, 6);
        maxheap_insert(heap, 10);

        if (maxheap_peek(heap) == 12)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 6)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        // Test deleting elements
        maxheap_delete(heap, 2); // Delete element at index 2 (value 10)

        if (maxheap_peek(heap) == 12)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 5)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        maxheap_delete(heap, 0); // Delete element at index 0 (value 12)

        if (maxheap_peek(heap) == 6)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 4)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        // Test inserting elements in descending order
        maxheap_insert(heap, 9);
        maxheap_insert(heap, 8);
        maxheap_insert(heap, 7);
        maxheap_insert(heap, 6);
        maxheap_insert(heap, 5);

        if (maxheap_peek(heap) == 9)
            printf("maxheap_peek() passed\n");

        if (maxheap_len(heap) == 9)
            printf("maxheap_len() passed\n");

        if (!maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        // Test deleting all elements
        while (heap->len > 0) {
            maxheap_delete(heap, 0);
        }

        if (maxheap_len(heap) == 0)
            printf("maxheap_len() passed\n");

        if (maxheap_is_empty(heap))
            printf("maxheap_is_empty() passed\n");

        maxheap_deinit(&heap);

        return 0;
}
