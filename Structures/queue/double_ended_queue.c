#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
        size_t rear;
        size_t front;

        size_t len;
        size_t capacity;
        int *data;
} Deque;


Deque* deque_init(size_t capacity) {
        Deque *deque = malloc(sizeof(Deque));
        if (!deque) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        deque->data = (int*)malloc(capacity * sizeof(int));
        if (!(deque->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(deque);
                exit(-1);
        }

        deque->capacity = capacity;
        deque->len = 0;

        deque->front = 0;
        deque->rear = 0;

        return deque;
}

void deque_deinit(Deque **self) {
        free((*self)->data); // Deallocate the data array
        free(*self); // Deallocate the double-ended queue

        *self = NULL; // Remove the pointer reference to the double-ended queue
}

int deque_is_empty(Deque *self) {
        return (self->len <= 0);
}

int deque_is_full(Deque *self) {
        return (self->len >= self->capacity);
}

size_t deque_len(Deque *self) {
        return self->len;
}

int deque_peek(const Deque *self) {
        if (self->len <= 0) {
                return -1;
        }

        return self->data[self->front];
}

void deque_enqueue_front(Deque *self, int val) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "error: fail to enqueue, deque is full!\n");
                return;
        }

        // The following condition is necessary to handle the circular nature of the deque.
        // It ensures that the front pointer moves in a circular manner, accounting for the
        // special case where the rear starts at '0' instead of '-1' in the array.
        if (self->len > 0) {
                // If the front reaches the first index, set it to the last index
                self->front = self->front == 0 ? self->capacity - 1 : self->front - 1;
        }

        self->data[self->front] = val;
        self->len++;
}

void deque_enqueue_rear(Deque *self, int val) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "error: fail to enqueue, deque is full!\n");
                return;
        }

        // The following condition is necessary to handle the circular nature of the deque.
        // It ensures that the rear pointer moves in a circular manner, accounting for the
        // special case where the rear starts at '0' instead of '-1' in the array.
        if (self->len > 0) {
                // If the rear reaches the last index, reset it to 0
                self->rear = (self->rear + 1) % self->capacity;
        }

        self->data[self->rear] = val;
        self->len++;
}

int deque_dequeue_front(Deque *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to dequeue, deque is empty!\n");
                return -1;
        }

        int temp = deque_peek(self);

        // Move the front pointer to the right in a circular manner
        self->front = (self->front + 1) % self->capacity;
        self->len--;

        return temp;
}

int deque_dequeue_rear(Deque *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to dequeue, deque is empty!\n");
                return -1;
        }

        int temp = deque_peek(self);

        // Move the rear pointer to the left in a circular manner
        self->rear = self->rear == 0 ? self->capacity - 1 : self->rear - 1;
        self->len--;

        return temp;
}

void deque_display(Deque *self) {
        if (self->len <= 0) {
                fprintf(stderr, "queue is empty!\n");
                return;
        }

        size_t i = self->front;
        for (size_t len = self->len; len > 0; len--) {
                printf("|%d", self->data[i]);
                i = (i + 1) % self->capacity;
        }
        printf("\n");
}

int main() {
        size_t capacity = 5;
        Deque *deque = deque_init(capacity);

        // Test case 1: Enqueue elements at the front and rear
        deque_enqueue_front(deque, 10);
        deque_enqueue_rear(deque, 20);
        deque_enqueue_front(deque, 30);
        deque_enqueue_rear(deque, 40);

        printf("Test Case 1 - Enqueue elements: ");
        deque_display(deque);  // Expected output: |30|10|20|40|

        // Test case 2: Dequeue elements from the front and rear
        deque_dequeue_front(deque);
        deque_dequeue_rear(deque);

        printf("\nTest Case 2 - Dequeue elements: ");
        deque_display(deque);  // Expected output: |10|20

        // Test case 3: Enqueue elements to fill the deque
        deque_enqueue_rear(deque, 50);
        deque_enqueue_rear(deque, 60);
        deque_enqueue_rear(deque, 70);

        printf("\nTest Case 3 - Enqueue elements to fill the deque: ");
        deque_display(deque);  // Expected output: |10|20|50|60|70|

        // Test case 4: Attempt to enqueue when the deque is full
        deque_enqueue_rear(deque, 80);  // Exceeds capacity, error message should be printed

        printf("\nTest Case 4 - Attempt to enqueue when the deque is full: \n");
        deque_display(deque);  // Expected output: |10|50|60|70|

        // Test case 5: Dequeue elements to empty the deque
        deque_dequeue_front(deque);
        deque_dequeue_front(deque);
        deque_dequeue_front(deque);
        deque_dequeue_front(deque);
        deque_dequeue_front(deque);

        printf("\nTest Case 5 - Dequeue elements to empty the deque: \n");
        deque_display(deque);  // Expected output: queue is empty!

        // Test case 6: Attempt to dequeue when the deque is empty
        deque_dequeue_front(deque);  // Deque is empty, error message should be printed

        printf("\nTest Case 6 - Attempt to dequeue when the deque is empty: \n");
        deque_display(deque);  // Expected output: queue is empty!

        deque_deinit(&deque);

        return 0;
}

