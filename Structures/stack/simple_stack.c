#include <stdio.h>

#define CAPACITY 20

int stack[CAPACITY];
int top = -1;


int stack_is_empty() {
        return (top <= 0);
}

int stack_len() {
        return (top + 1);
}

int stack_is_full() {
        return (top + 1 >= CAPACITY);
}

int stack_peek() {
        return stack[top];
}

void stack_push(int val) {
        if (stack_len() >= CAPACITY) {
                printf("Stack Overflow\n");
                return;
        }

        stack[++top] = val;
}

void stack_pop() {
        if (stack_is_empty()) {
                printf("Stack Underflow\n");
                return;
        }

        top--;
}

int main() {
        // Test empty stack
        printf("Is the stack empty? %s\n", stack_is_empty() ? "Yes" : "No");

        // Test push and peek
        stack_push(10);
        stack_push(20);
        stack_push(30);
        printf("Top element: %d\n", stack_peek());

        // Test pop
        stack_pop();
        printf("Popped element\n");

        // Test stack length
        printf("Stack length: %d\n", stack_len());

        return 0;
}
