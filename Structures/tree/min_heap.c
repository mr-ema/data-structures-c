#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct MinHeap {
        int *data;
        size_t capacity;
        size_t len;
} MinHeap;


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

MinHeap* minheap_init(size_t capacity) {
        MinHeap *heap = malloc(sizeof(MinHeap));
        if (!heap) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        heap->data = (int*)malloc(capacity * sizeof(int));
        if (!(heap->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(heap);
                exit(-1);
        }

        heap->len       = 0;
        heap->capacity  = capacity;

        return heap;
}

void minheap_deinit(MinHeap **self) {
        free((*self)->data); // Free the memory for the array
        free(*self); // Free the memory for the MinHeap struct

        *self = NULL; // Remove the pointer reference to the heap
}

size_t minheap_len(const MinHeap *self) {
        return self->len;
}

int minheap_is_empty(const MinHeap *self) {
        return (self->len <= 0);
}

int minheap_peek(MinHeap *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: heap is empty!\n");
                return -1;
        }

        return (self->data[0]);
}

void minheap_heapify_up(MinHeap *self, size_t idx) {
        int *heap = self->data;

        while (idx > 0 && heap[parent_idx(idx)] > heap[idx]) {
                xor_swap(&heap[idx], &heap[parent_idx(idx)]);
                idx = parent_idx(idx);
        }
}

void minheap_heapify_down(MinHeap *self, size_t idx) {
        int *heap = self->data;
        size_t len = self->len;

        while (1) {
                size_t smallest = idx;
                size_t left     = left_child_idx(idx);
                size_t right    = right_child_idx(idx);

                if (left < len && heap[left] < heap[smallest])
                        smallest = left;

                if (right < len && heap[right] < heap[smallest])
                        smallest = right;

                if (smallest == idx)
                        break;

                xor_swap(&heap[idx], &heap[smallest]);
                idx = smallest;
        }
}

void minheap_insert(MinHeap *self, int key) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "overflow: could not insert key!\n");
                return;
        }

        size_t idx = self->len;
        self->len++;
        self->data[idx] = key;

        // Maintain the min heap property by swapping the element with its parent as long as necessary
        minheap_heapify_up(self, idx);
}

void minheap_delete(MinHeap *self, int idx) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to delete, the heap is empty!\n");
                return;
        } else if (idx >= self->len) {
                fprintf(stderr, "invalid index: index is out of bounds!\n");
                return;
        }

        // Swap the index of the key to be deleted with the index of the last key in the heap
        self->data[idx] = self->data[self->len - 1];
        self->len--; // delete last key (key to be delete)

        if (idx == 0 || self->data[idx] > self->data[parent_idx(idx)])
                minheap_heapify_down(self, idx);
        else
                minheap_heapify_up(self, idx);
}

int main() {
        MinHeap* heap = minheap_init(10);

        // Test inserting elements
        minheap_insert(heap, 5);
        minheap_insert(heap, 3);
        minheap_insert(heap, 8);
        minheap_insert(heap, 2);
        minheap_insert(heap, 9);

        if (minheap_peek(heap) == 2)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 5)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        // Test deleting elements
        minheap_delete(heap, 1); // Delete element at index 1 (value 3)

        if (minheap_peek(heap) == 2)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 4)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        minheap_delete(heap, 0); // Delete element at index 0 (value 2)

        if (minheap_peek(heap) == 5)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 3)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        // Test inserting more elements
        minheap_insert(heap, 12);
        minheap_insert(heap, 6);
        minheap_insert(heap, 10);

        if (minheap_peek(heap) == 5)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 6)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        // Test deleting elements
        minheap_delete(heap, 2); // Delete element at index 2 (value 10)

        if (minheap_peek(heap) == 5)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 5)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        minheap_delete(heap, 0); // Delete element at index 0 (value 5)

        if (minheap_peek(heap) == 6)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 4)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        // Test inserting elements in descending order
        minheap_insert(heap, 9);
        minheap_insert(heap, 8);
        minheap_insert(heap, 7);
        minheap_insert(heap, 6);
        minheap_insert(heap, 5);

        if (minheap_peek(heap) == 5)
            printf("minheap_peek() passed\n");

        if (minheap_len(heap) == 9)
            printf("minheap_len() passed\n");

        if (!minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        // Test deleting all elements
        while (minheap_len(heap) > 0) {
            minheap_delete(heap, 0);
        }

        if (minheap_len(heap) == 0)
            printf("minheap_len() passed\n");

        if (minheap_is_empty(heap))
            printf("minheap_is_empty() passed\n");

        minheap_deinit(&heap);

        return 0;
}
