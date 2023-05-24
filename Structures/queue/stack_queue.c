#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "lib/stack.h"

DECLARE_STACK(Stack, int);
typedef struct {
        Stack *stack1;
        Stack *stack2;
} Queue;

Queue* queue_init(size_t capacity) {
        Queue *queue = malloc(sizeof(Queue));
        if (!queue) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        queue->stack1 = (Stack*)stack_init(capacity);
        queue->stack2 = (Stack*)stack_init(capacity);

        return queue;
}

void queue_deinit(Queue **self) {
        // Deallocate Stacks
        stack_deinit(&(*self)->stack1);
        stack_deinit(&(*self)->stack2);

        free(*self); // Deallocate queue

        *self = NULL; // Remove the pointer reference to the queue
}

size_t queue_len(const Queue *self) {
        return stack_len(self->stack1);
}

int queue_is_empty(const Queue *self) {
        return stack_is_empty(self->stack1);
}

int queue_peek(const Queue *self) {
        if (stack_is_empty(self->stack1)) {
                return -1;
        }

        return self->stack1->data[0];
}

void queue_enqueue(Queue *self, int value) {
        if (stack_is_full(self->stack1)) {
                fprintf(stderr, "error: fail to enqueue, queue is full!\n");
                return;
        }

        stack_push(self->stack1, value);
}

int queue_dequeue(Queue *self) {
        if (stack_is_empty(self->stack1)) {
                fprintf(stderr, "error: fail to dequeue, queue is empty!\n");
                return -1;
        }

        while (!stack_is_empty(self->stack1))
                stack_push(self->stack2, stack_pop(self->stack1));

        int rem_elem = stack_pop(self->stack2); // Remove the element
        while (!stack_is_empty(self->stack2))
                stack_push(self->stack1, stack_pop(self->stack2));

        return rem_elem;
}

void queue_display(Queue *self) {
        if (queue_is_empty(self)) {
                fprintf(stderr, "queue is empty!\n");
                return;
        }

        for (size_t i = 0; i < queue_len(self); i++) {
                printf("|%d", self->stack1->data[i]);
        }
        printf("\n");
}

int main() {
        Queue* queue = queue_init(6);

        // Test enqueueing elements
        queue_enqueue(queue, 5);
        queue_enqueue(queue, 3);
        queue_enqueue(queue, 8);
        queue_enqueue(queue, 2);
        queue_enqueue(queue, 9);

        printf("[01] %s\n", (queue_peek(queue) == 5)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[02] %s\n", (queue_len(queue) == 5)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[03] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");

        // Test dequeueing elements
        printf("[04] %s\n", (queue_dequeue(queue) == 5) ? "queue_dequeue()   [passed]" : "queue_dequeue()  [failed]");
        printf("[05] %s\n", (queue_peek(queue) == 3)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[06] %s\n", (queue_len(queue) == 4)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[07] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");

        // Test enqueueing more elements
        queue_enqueue(queue, 12);
        queue_enqueue(queue, 6);

        printf("[09] %s\n", (queue_peek(queue) == 3)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[10] %s\n", (queue_len(queue) == 6)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[11] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");

        // Test dequeueing elements
        printf("[14] %s\n", (queue_dequeue(queue) == 3) ? "queue_dequeue()   [passed]" : "queue_dequeue()  [failed]");
        printf("[15] %s\n", (queue_peek(queue) == 8)    ? "queue_peek()      [passed]" : "queue_peek()     [failed]");
        printf("[16] %s\n", (queue_len(queue) == 5)     ? "queue_len()       [passed]" : "queue_len()      [failed]");
        printf("[17] %s\n", (!queue_is_empty(queue))    ? "queue_is_empty()  [passed]" : "queue_is_empty() [failed]");

        // Test displaying the queue
        printf("[18] %s", "expecting: |8|2|9|12|6 / result: ");
        queue_display(queue);

        queue_deinit(&queue);

        return 0;
}
