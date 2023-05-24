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

void reverse_expression(char *expression, size_t size) {
        char stack[size + 1];
        int top = 0;

        for (int i = size - 1; i >= 0; i--) { 
                if (!expression[i]) {
                        continue;
                }
                if (expression[i] == '(') {
                        stack[top++] = ')';
                        continue;
                }
                if (expression[i] == ')') {
                        stack[top++] = '(';
                        continue;
                }

                stack[top++] = expression[i];
        }

        stack[top] = '\0';
        strcpy(expression, stack);
}

char* infix_to_postfix(const char* expression, size_t size) {
        Stack *stack = stack_init(size);

        char* result = (char*)malloc(size * sizeof(char));
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
                        while (precedence(stack_peek(stack)) >= precedence(*expression)) {
                                // Special case when converting to prefix
                                if (*expression != '^' && precedence(*expression) == precedence(stack_peek(stack))) {
                                        break;
                                }
                                *result_ptr++ = stack_pop(stack);
                        }
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

void infix_to_prefix(char *expression, size_t size) {
        reverse_expression(expression, size);

        char* postfix = infix_to_postfix(expression, size);
        reverse_expression(postfix, size);

        strcpy(expression, postfix);
        free(postfix);
}

int main(void) {
        char t1[] = "x^y/(5*z)+2";
        infix_to_prefix(t1, strlen(t1));

        if (strcmp(t1, "+/^xy*5z2") == 0) {
                printf("TEST PASS:  %s\n", t1);
        } else {
                printf("TEST FAILED: EXPECTED +/^xy*5z2 GOT %s\n", t1);
        }

        char t2[] = "k+l-m*n+(o^p)*w/u/v*t+q";
        infix_to_prefix(t2, strlen(t2));

        if (strcmp(t2, "++-+kl*mn*//*^opwuvtq") == 0) {
                printf("TEST PASS: %s\n", t2);
        } else {
                printf("TEST FAILED: EXPECTED ++-+kl*mn*//*^opwuvtq GOT %s\n", t2);
        }
}
