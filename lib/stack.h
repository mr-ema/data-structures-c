#ifndef STACK_H
#define STACK_H

/**
 * stack.h
 *
 * Header file for a generic stack implementation.
 *
 * Usage:
 * 1. Include this header file in your source code: #include "stack.h"
 * 2. Define a stack type using the DECLARE_STACK macro.
 *    Example: DECLARE_STACK(MyStack, int) declares a stack type named MyStack that stores integers.
 * 3. Use the provided stack functions to work with the stack.
 *
 * The stack implementation provides the following functions:
 *
 * - typename* stack_init(size_t capacity):
 *   Initializes a new stack with the specified capacity and returns a pointer to the stack.
 *
 * - void stack_deinit(typename **stack):
 *   Deinitializes the stack and frees the allocated memory. Sets the stack pointer to nil.
 *
 * - int stack_is_empty(const typename *stack):
 *   Checks if the stack is empty. Returns 1 if the stack is empty, 0 otherwise.
 *
 * - int stack_is_full(const typename *stack):
 *   Checks if the stack is full. Returns 1 if the stack is full, 0 otherwise.
 *
 * - size_t stack_len(const typename *stack):
 *   Returns the number of elements currently in the stack.
 *
 * - int stack_peek(const typename *stack):
 *   Retrieves the top element of the stack without removing it.
 *   Returns the top element if the stack is not empty, nil otherwise.
 *
 * - void stack_push(typename *stack, type val):
 *   Pushes a new element onto the stack.
 *   If the stack is full, an error message is printed to stderr and no element is added.
 *
 * - type stack_pop(typename *stack):
 *   Removes and returns the top element from the stack.
 *   If the stack is empty, an error message is printed to stderr and nil is returned.
 *
 * Note: 
 * - The "typename" parameter in the DECLARE_STACK macro is a placeholder for the actual stack type name.
 *   Replace "typename" with a meaningful name when using the macro.
 * - The "type" parameter in the DECLARE_STACK macro is the data type of the elements stored in the stack.
 *   Replace "type" with the desired data type when using the macro.
 * - Make sure to call stack_deinit() to free the memory allocated by the stack.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define nil 0

#define DECLARE_STACK(typename, type)   \
        typedef struct {                \
                size_t top;             \
                size_t len;             \
                size_t capacity;        \
                type *data;             \
        } typename;                     \
                                        \
                                        \
/* Initializes a new stack with the specified capacity and returns a pointer to the stack. */ \
typename* stack_init(size_t capacity) {                                 \
        typename* stack = malloc(sizeof(typename));                     \
        if (!stack) {                                                   \
                fprintf(stderr, "error: memory allocation failed!\n");  \
                exit(-1);                                               \
        }                                                               \
                                                                        \
        stack->data = (type*)malloc(capacity * sizeof(type));           \
        if (!(stack->data)) {                                           \
                fprintf(stderr, "error: memory allocation failed!\n");  \
                                                                        \
                free(stack);                                            \
                exit(-1);                                               \
        }                                                               \
                                                                        \
        stack->capacity = capacity;                                     \
        stack->len      = 0;                                            \
        stack->top      = 0;                                            \
                                                                        \
        return stack;                                                   \
}                                                                       \
                                                                        \
/* Deinitializes the stack and frees the allocated memory. Sets the stack pointer to nil. */ \
void stack_deinit(typename **stack) {   \
        free((*stack)->data);           \
        free(*stack);                   \
                                        \
        *stack = (typename *)0;         \
}                                       \
                                        \
/* Checks if the stack is empty. Returns 1 if the stack is empty, 0 otherwise. */ \
int stack_is_empty(const typename *stack) {     \
        return (stack->len <= 0);               \
}                                               \
                                                \
/* Checks if the stack is full. Returns 1 if the stack is full, 0 otherwise. */ \
int stack_is_full(const typename *stack) {      \
        return (stack->len >= stack->capacity); \
}                                               \
                                                \
/* Returns the number of elements currently in the stack. */ \
size_t stack_len(const typename *stack) {       \
        return stack->len;                      \
}                                               \
                                                \
/* Retrieves the element at the top of the stack without removing it. \
 * Returns the top element if the stack is not empty, nil otherwise. */ \
type stack_peek(const typename *stack) {        \
        if (stack->len <= 0) {                  \
                return nil;                     \
        }                                       \
                                                \
        return stack->data[stack->top];         \
}                                               \
                                                \
/* Adds a new element to the top of the stack. \
 * If the stack is full, an error message is printed to stderr and no element is added. */ \
void stack_push(typename *stack, type val) {                            \
        if (stack->len >= stack->capacity) {                            \
                fprintf(stderr, "error: push fail, stack is full!\n");  \
                return;                                                 \
        }                                                               \
                                                                        \
        if (stack->len > 0) {                                           \
                stack->top++;                                           \
        }                                                               \
                                                                        \
        stack->data[stack->top] = val;                                  \
        stack->len++;                                                   \
}                                                                       \
                                                                        \
/* Removes and returns the element from the top of the stack. \
 * If the stack is empty, an error message is printed to stderr and nil is returned. */ \
type stack_pop(typename *stack) {                                       \
        if (stack->len-- <= 0) {                                        \
                fprintf(stderr, "error: pop fail, stack is empty!\n");  \
                return nil;                                             \
        }                                                               \
                                                                        \
        if (stack->len <= 0) {                                          \
                return stack->data[stack->top];                         \
        };                                                              \
                                                                        \
        return stack->data[stack->top--];                               \
}                                                                       \

#endif /* STACK_H */
