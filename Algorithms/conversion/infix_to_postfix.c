#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/stack.h"
DECLARE_STACK(Stack, char);


int precedence(const char operator) {
        if (operator == '^')
                return 3;
        if (operator == '*' || operator == '/')
                return 2;
        if (operator == '+' || operator == '-')
                return 1;

        return 0;
}

int is_operator(const char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

int is_parentesis(const char ch) {
        return (ch == '(' || ch == ')');
}

char* infix_to_postfix(const char* expression, size_t size) {
        Stack *stack = stack_init(size);

        char *result = (char*)malloc(size * sizeof(char));
        char *result_ptr = result;

        for ( ; *expression != '\0'; expression++) {
                if (!is_operator(*expression)) {
                        *result_ptr++ = *expression;
                } else if (*expression == '(') {
                        stack_push(stack, *expression);
                } else if (*expression == ')') {
                         while (stack_peek(stack) != '(') {
                                *result_ptr++ = stack_pop(stack);
                        }
                        stack_pop(stack); // Pop '(' from the stack
                } else {
                        while (precedence(stack_peek(stack)) >= precedence(*expression))
                                *result_ptr++ = stack_pop(stack);
                        stack_push(stack, *expression);
                }
        }

        // Clear the stack
        while (!stack_is_empty(stack)) {
                *result_ptr++ = stack_pop(stack);
        }

        *result_ptr = '\0';
        stack_deinit(&stack);

        return result;
}

int main(void) {
        char t1[] = "x^y/(5*z)+2";
        char* result1 = infix_to_postfix(t1, sizeof(t1) - 1);

        if (strcmp(result1, "xy^5z*/2+") == 0) {
                printf("TEST PASS: %s\n", result1);
        } else {
                printf("TEST FAILED: EXPECTED xy^5z*/2+ GOT %s\n", result1);
        }

        free(result1);

        char t2[] = "k+l-m*n+(o^p)*w/u/v*t+q";
        char* result2 = infix_to_postfix(t2, sizeof(t2) - 1);

        if (strcmp(result2, "kl+mn*-op^w*u/v/t*+q+") == 0) {
                printf("TEST PASS: %s\n", result2);
        } else {
                printf("TEST FAILED: EXPECTED kl+mn*-op^w*u/v/t*+q+ GOT %s\n", result2);
        }

        free(result2);

        return 0;
}
