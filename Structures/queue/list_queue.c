#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
        int data;
        struct Node *next;
} Node;

typedef struct {
        struct Node *front;
        struct Node *rear;
        size_t len;
} Queue;


Queue* queue_init() {
        Queue *queue = malloc(sizeof(Queue));
        if (!queue) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        queue->rear = NULL;
        queue->front = NULL;
        queue->len = 0;

        return queue;
}

void free_list_recursive(Node *node) {
        if (!node)
                return;

        free_list_recursive(node->next);

        free(node);
}

void queue_deinit(Queue **self) {
        free_list_recursive((*self)->front); // Deallocate queue elements
        free(*self); // Deallocate queue

        *self = NULL; // Remove the pointer reference to the queue
}

Node* new_node(int val, Node *next) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->data = val;
        node->next = next;

        return node;
}

int queue_is_empty(Queue *self) {
        return (self->len <= 0);
}

size_t queue_len(Queue *self) {
        return (self->len);
}

int queue_peek(Queue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "queue is empty!\n");
                return -1;
        }

        return (self->front->data);
}

void queue_enqueue(Queue *self, int val) {
        if (self->len <= 0) {
                self->front = new_node(val, 0);
                self->rear = self->front;
        } else {
                self->rear->next = new_node(val, 0);
                self->rear = self->rear->next;
        }

        self->len++;
}

int queue_dequeue(Queue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to dequeue, queue is empty!\n");
                return -1;
        }

        int rem_elem = self->front->data;

        Node* temp = self->front;
        self->front = temp->next;

        free(temp);
        self->len--;

        return rem_elem;
}

void queue_display(Queue *self) {
        if (self->len <= 0) {
                fprintf(stderr, "queue is empty!\n");
                return;
        }

        for (Node* temp = self->front; temp != 0; temp = temp->next)
                printf("|%d", temp->data);
        printf("|\n");
}

int main() {
        Queue* queue = queue_init();

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
