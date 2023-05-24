#ifndef QUEUE_H
#define QUEUE_H

/**
 * queue.h
 *
 * Header file for a generic queue implementation.
 *
 * Usage:
 * 1. Include this header file in your source code: #include "queue.h"
 * 2. Define a queue type using the DECLARE_QUEUE macro.
 *    Example: DECLARE_QUEUE(MyQueue, int) declares a queue type named MyQueue that stores integers.
 * 3. Use the provided queue functions to work with the queue.
 *
 * The queue implementation provides the following functions:
 *
 * - typename* queue_init(size_t capacity):
 *   Initializes a new queue with the specified capacity and returns a pointer to the queue.
 *
 * - void queue_deinit(typename **queue):
 *   Deinitializes the queue and frees the allocated memory. Sets the queue pointer to nil.
 *
 * - size_t queue_len(const typename *queue):
 *   Returns the number of elements currently in the queue.
 *
 * - int queue_is_full(const typename *queue):
 *   Checks if the queue is full. Returns 1 if the queue is full, 0 otherwise.
 *
 * - int queue_is_empty(const typename *queue):
 *   Checks if the queue is empty. Returns 1 if the queue is empty, 0 otherwise.
 *
 * - type queue_peek(const typename *queue):
 *   Retrieves the element at the front of the queue without removing it.
 *   Returns the front element if the queue is not empty, nil otherwise.
 *
 * - void queue_enqueue(typename *queue, type value):
 *   Adds a new element to the rear of the queue.
 *   If the queue is full, an error message is printed to stderr and no element is added.
 *
 * - type queue_dequeue(typename *queue):
 *   Removes and returns the element from the front of the queue.
 *   If the queue is empty, an error message is printed to stderr and nil is returned.
 *
 * Note: 
 * - The "typename" parameter in the DECLARE_QUEUE macro is a placeholder for the actual queue type name.
 *   Replace "typename" with a meaningful name when using the macro.
 * - The "type" parameter in the DECLARE_QUEUE macro is the data type of the elements stored in the queue.
 *   Replace "type" with the desired data type when using the macro.
 * - Make sure to call queue_deinit() to free the memory allocated by the queue.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define nil 0

#define DECLARE_QUEUE(typename, type) \
        typedef struct { \
                size_t rear; \
                size_t front; \
\
                size_t len; \
                size_t capacity; \
                type *data; \
        } typename; \
\
\
/* Initializes a new queue with the specified capacity and returns a pointer to the queue. */ \
typename* queue_init(size_t capacity) { \
        typename *queue = malloc(sizeof(typename)); \
        if (!queue) { \
                fprintf(stderr, "error: memory allocation failed!\n"); \
                exit(-1); \
        } \
\
        queue->data = (type*)malloc(capacity * sizeof(type)); \
        if (!(queue->data)) { \
                fprintf(stderr, "error: memory allocation failed!\n"); \
                exit(-1); \
        } \
\
        queue->capacity = capacity; \
        queue->len = 0; \
\
        queue->front = 0; \
        queue->rear = 0; \
\
        return queue; \
} \
\
/* Deinitializes the queue and frees the allocated memory. Sets the queue pointer to nil. */ \
void queue_deinit(typename **queue) { \
        free((*queue)->data); \
        free(*queue); \
\
        *queue = (typename *)0; \
} \
\
/* Returns the number of elements currently in the queue. */ \
size_t queue_len(typename *queue) { \
        return queue->len; \
} \
\
/* Checks if the queue is full. Returns 1 if the queue is full, 0 otherwise. */ \
int queue_is_full(typename *queue) { \
        return (queue->len >= queue->capacity); \
} \
\
/* Checks if the queue is empty. Returns 1 if the queue is empty, 0 otherwise. */ \
int queue_is_empty(typename *queue) { \
        return (queue->len <= 0); \
} \
\
/* Retrieves the element at the front of the queue without removing it. \
 * Returns the front element if the queue is not empty, nil otherwise. */ \
type queue_peek(typename *queue) { \
        if (queue->len <= 0) { \
                return nil; \
        } \
\
        return queue->data[queue->front]; \
} \
\
/* Adds a new element to the rear of the queue. \
 * If the queue is full, an error message is printed to stderr and no element is added. */ \
void queue_enqueue(typename *queue, type value) { \
        if (queue->len >= queue->capacity) { \
                fprintf(stderr, "error: fail to enqueue, queue is full!\n"); \
                return; \
        } \
\
        queue->data[queue->rear] = value; \
        queue->rear = (queue->rear + 1) % queue->capacity; \
        queue->len++; \
} \
\
/* Removes and returns the element from the front of the queue. \
 * If the queue is empty, an error message is printed to stderr and nil is returned. */ \
type queue_dequeue(typename *queue) { \
        if (queue->len <= 0) { \
                fprintf(stderr, "error: fail to dequeue, queue is empty!\n"); \
                return nil; \
        } \
\
        type temp = queue->data[queue->front]; \
\
        queue->front = (queue->front + 1) % queue->capacity; \
        queue->len--; \
\
        return temp; \
} \

#endif /* QUEUE_H */
