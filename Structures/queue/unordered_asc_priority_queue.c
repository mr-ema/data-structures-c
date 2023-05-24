#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
        int val;
        int priority;
} Item;

typedef struct {
        size_t capacity;
        size_t len;

        Item *data;
} PQueue;


PQueue* pqueue_init(size_t capacity) {
        PQueue *queue = malloc(sizeof(PQueue));
        if (!queue) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        queue->data = (Item*)malloc(sizeof(Item) * capacity);
        if (!(queue->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(queue);
                exit(-1);
        }

        queue->capacity = capacity;
        queue->len = 0;

        return queue;
}

void pqueue_deinit(PQueue **self) {
        free((*self)->data); // Deallocate priority queue data array
        free(*self); // Deallocate priority queue

        *self = NULL; // Remove the pointer reference to the queue
}

int pqueue_is_full(PQueue *self) {
        return (self->len >= self->capacity);
}

int pqueue_is_empty(PQueue *self) {
        return  (self->len <= 0);
}

size_t pqueue_len(PQueue *self) {
        return self->len;
}

int pqueue_peek(PQueue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "queue is empty!\n");
                return -1;
        }

        int idx = 0;
        for (size_t i = 0; i < self->len; i++) {
                if (self->data[i].priority > self->data[idx].priority) {
                        idx = i;
                }
        }

        return self->data[idx].val;
}

void pqueue_enqueue(PQueue *self, int value, int priority) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "error: fail to enqueue, queue is full!\n");
                return;
        }

        Item item = { .val = value, .priority = priority };

        self->data[self->len++] = item;
}

size_t get_highest_priority_idx(PQueue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "queue is empty!\n");
                return 0;
        }

        int idx = 0;
        for (size_t i = 0; i < self->len; i++) {
                if (self->data[i].priority > self->data[idx].priority) {
                        idx = i;
                }
        }

        return idx;
}

int pqueue_dequeue(PQueue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to dequeue, queue is empty!\n");
                return -1;
        }

        size_t item_idx = get_highest_priority_idx(self);
        int del_item    = self->data[item_idx].val;

        self->data[item_idx] = self->data[self->len - 1];
        self->len--;

        return del_item;
}

int main() {
        // Initialize the priority queue with a capacity of 5
        PQueue *queue = pqueue_init(5);

        // Enqueue items with different priorities
        pqueue_enqueue(queue, 10, 2);
        pqueue_enqueue(queue, 20, 3);
        pqueue_enqueue(queue, 30, 1);
        pqueue_enqueue(queue, 40, 5);
        pqueue_enqueue(queue, 50, 4);

        // Get the length of the priority queue
        printf("Priority queue length: %ld\n", pqueue_len(queue));

        // Peek at the item with the highest priority
        int highest_priority_item = pqueue_peek(queue);
        printf("Item with the highest priority: %d\n", highest_priority_item);

        // Dequeue items and print them
        printf("Dequeued items: ");
        while (!pqueue_is_empty(queue)) {
            int item = pqueue_dequeue(queue);
            printf("%d ", item);
        }
        printf("\n");

        // Enqueue more items
        pqueue_enqueue(queue, 60, 1);
        pqueue_enqueue(queue, 70, 2);
        pqueue_enqueue(queue, 80, 3);

        // Peek at the item with the highest priority
        highest_priority_item = pqueue_peek(queue);
        printf("Item with the highest priority: %d\n", highest_priority_item);

        // Dequeue items and print them
        printf("Dequeued items: ");
        while (!pqueue_is_empty(queue)) {
            int item = pqueue_dequeue(queue);
            printf("%d ", item);
        }
        printf("\n");

        // Deinitialize the priority queue
        pqueue_deinit(&queue);

        return 0;
}
