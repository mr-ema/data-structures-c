#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
        size_t rear;
        size_t front;

        size_t len;
        size_t capacity;
        int *data;
} Queue;


Queue* queue_init(size_t capacity) {
        Queue *queue = malloc(sizeof(Queue));
        if (!queue) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        queue->data = (int*)malloc(capacity * sizeof(int));
        if (!(queue->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        queue->capacity = capacity;
        queue->len = 0;

        queue->front = 0;
        queue->rear = 0;

        return queue;
}

void queue_deinit(Queue **self) {
        free((*self)->data);    // Deallocate queue elements
        free(*self);            // Deallocate queue

        *self = NULL; // Remove the pointer reference to the queue
}

size_t queue_len(Queue *self) {
        return self->len;
}

int queue_is_full(Queue *self) {
        return (self->len >= self->capacity);
}

int queue_is_empty(Queue *self) {
        return (self->len <= 0);
}

int queue_peek(Queue *self) {
        if (self->len <= 0)
                return -1;

        return self->data[self->front];
}

void queue_enqueue(Queue *self, int value) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "error: fail to enqueue, queue is full!\n");
                return;
        }

        self->data[self->rear] = value;
        self->rear = (self->rear + 1) % self->capacity;
        self->len++;
}

int queue_dequeue(Queue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to dequeue, queue is empty!\n");
                return -1;
        }

        int temp = self->data[self->front];

        self->front = (self->front + 1) % self->capacity;
        self->len--;

        return temp;
}

void queue_display(Queue *self) {
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
        Queue* queue = queue_init(5);

        // Test enqueueing elements
        queue_enqueue(queue, 5);
        queue_enqueue(queue, 3);
        queue_enqueue(queue, 8);
        queue_enqueue(queue, 2);
        queue_enqueue(queue, 9);

        printf("[01] %s\n", (queue_peek(queue) == 5)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[02] %s\n", (queue_len(queue) == 5)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[03] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");
        printf("[04] %s\n", (queue_is_full(queue))      ? "queue_is_full()   [passed]" : "queue_is_full()  [failed]");

        // Test dequeueing elements
        printf("[05] %s\n", (queue_dequeue(queue) == 5) ? "queue_dequeue()   [passed]" : "queue_dequeue()  [failed]");
        printf("[06] %s\n", (queue_peek(queue) == 3)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[07] %s\n", (queue_len(queue) == 4)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[08] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");
        printf("[09] %s\n", (!queue_is_full(queue))     ? "queue_is_full()   [passed]" : "queue_is_full()  [failed]");

        // Test enqueueing more elements
        queue_enqueue(queue, 12);
        queue_enqueue(queue, 6);

        printf("[10] %s\n", (queue_peek(queue) == 3)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[11] %s\n", (queue_len(queue) == 5)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[12] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");
        printf("[13] %s\n", (queue_is_full(queue))      ? "queue_is_full()   [passed]" : "queue_is_full()  [failed]");

        // Test dequeueing elements
        printf("[14] %s\n", (queue_dequeue(queue) == 3) ? "queue_dequeue()   [passed]" : "queue_dequeue()  [failed]");
        printf("[15] %s\n", (queue_peek(queue) == 8)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[16] %s\n", (queue_len(queue) == 4)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[17] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");
        printf("[18] %s\n", (!queue_is_full(queue))     ? "queue_is_full()   [passed]" : "queue_is_full()  [failed]");

        // Test displaying the queue
        printf("[19] %s", "expecting: |8|2|9|12 / result: ");
        queue_display(queue);

        queue_deinit(&queue);

        return 0;
}
