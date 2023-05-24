#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
        size_t top;

        size_t len;
        size_t capacity;
        int *data;
} Stack;


Stack* stack_init(size_t capacity) {
        Stack* stack = malloc(sizeof(Stack));
        if (!stack) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        stack->data = (int*)malloc(capacity * sizeof(int));
        if (!(stack->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(stack);
                exit(-1);
        }

        stack->capacity = capacity;
        stack->len = 0;
        stack->top = 0;

        return stack;
}

void stack_deinit(Stack **self) {
        free((*self)->data); // Free stack array
        free(*self); // Free Stack structure

        *self = NULL; // Remove the pointer reference to the stack
}

int stack_is_empty(const Stack *self) {
        return (self->len <= 0);
}

int stack_is_full(const Stack *self) {
        return (self->len >= self->capacity);
}

size_t stack_len(const Stack *self) {
        return self->len;
}

int stack_peek(const Stack *self) {
        if (self->len <= 0) {
                fprintf(stderr, "stack is empty!\n");
                return -1;
        }

        return self->data[self->top];
}

void stack_push(Stack *self, int val) {
        if (self->len >= self->capacity) {
                fprintf(stderr, "error: push fail, stack is full!\n");
                return;
        }

        /* 'top' is an unsigned integer of type 'size_t', which cannot represent negative values.
         * We increment 'top' only after the first insertion to ensure it remains a valid index.
         * This approach accounts for the unsigned nature of 'size_t' and guarantees the correctness of 'top'. */
        if (self->len > 0) {
                self->top++;
        }

        self->data[self->top] = val;
        self->len++;
}

int stack_pop(Stack *self) {
        if (self->len-- <= 0) {
                fprintf(stderr, "error: pop fail, stack is empty!\n");
                return -1;
        }

        if (self->len <= 0)
                return self->data[self->top];

        return self->data[self->top--];
}

int main() {
        Stack* stack = stack_init(5);

        // Test stack_is_empty()
        printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

        // Test stack_push()
        stack_push(stack, 10);
        stack_push(stack, 20);
        stack_push(stack, 30);

        // Test stack_len()
        printf("Stack length: %zu\n", stack_len(stack));

        // Test stack_is_full()
        printf("Is stack full? %s\n", stack_is_full(stack) ? "Yes" : "No");

        // Test stack_peek()
        printf("Top element: %d\n", stack_peek(stack));

        // Test stack_pop()
        printf("Popped element: %d\n", stack_pop(stack));

        // Test stack_push() after pop
        stack_push(stack, 40);

        // Test stack_len() after push
        printf("Stack length: %zu\n", stack_len(stack));

        // Test stack_pop() until empty
        printf("Popping all elements: ");
        while (!stack_is_empty(stack)) {
            printf("%d ", stack_pop(stack));
        }
        printf("\n");

        // Test stack_is_empty() after popping
        printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

        // Test stack_peek() on an empty stack
        printf("Peeking on an empty stack: %d\n", stack_peek(stack));

        // Test stack_pop() on an empty stack
        printf("Popping from an empty stack: %d\n", stack_pop(stack));

        // Deallocate the stack
        stack_deinit(&stack);
}
