#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
        int data;
        struct Node *next;
} Node;

typedef struct {
        struct Node *top;
        size_t len;
} Stack;


Stack* stack_init() {
        Stack *stack = malloc(sizeof(Stack));
        if (!stack) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        stack->len = 0;
        stack->top = NULL;

        return stack;
}

void free_list_recursive(Node *node) {
        if (!node)
                return;

        free_list_recursive(node->next);

        free(node);
}

void stack_deinit(Stack **self) {
        free_list_recursive((*self)->top); // Deallocate the entire list
        free(*self); // Deallocate the stack

        *self = NULL; // Remove the pointer reference to the stack
}

Node* new_node(int value, Node *next) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->data = value;
        node->next = next;

        return node;
}

int stack_is_empty(const Stack *self) {
        return (self->len <= 0);
}

size_t stack_len(const Stack *self) {
        return (self->len);
}

int stack_peek(const Stack *self) {
        if (self->len <= 0) {
                fprintf(stderr, "stack is empty!\n");
                return -1;
        }

        return self->top->data;
}

void stack_push(Stack *self, int value) {
        Node *prev = self->top;
        self->top = new_node(value, prev);

        self->len++;
}

int stack_pop(Stack *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to pop, stack is empty!\n");
                return -1;
        }

        int item = self->top->data;

        Node *temp  = self->top;
        self->top = temp->next;

        free(temp);
        self->len--;

        return item;
}

int main() {
        Stack* stack = stack_init();

        // Test stack_is_empty()
        printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

        // Test stack_push()
        stack_push(stack, 10);
        stack_push(stack, 20);
        stack_push(stack, 30);

        // Test stack_len()
        printf("Stack length: %zu\n", stack_len(stack));

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
