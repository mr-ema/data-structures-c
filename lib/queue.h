#ifndef QUEUE_H
#define QUEUE_H

#define MAX_ARRAY_SIZE 20 

#include <stdio.h>

/******************
 * circular queue *
 ******************/

typedef struct {
        int rear;
        int front;
        void* queue[MAX_ARRAY_SIZE];
} queue_t;

static inline void queue_init(queue_t *q)
{
        q->rear = -1;
        q->front = -1;
}

static inline int queue_is_empty(queue_t *q)
{
        return (q->rear <= -1 && q->front <= -1);
}

static inline int queue_is_full(queue_t *q) {
        return ((q->rear + 1) % MAX_ARRAY_SIZE == q->front);
}

static inline int queue_len(queue_t *q)
{
        if (queue_is_empty(q))
                return 0;

        if (q->rear < q->front)
                return (MAX_ARRAY_SIZE - q->front) + (q->rear + 1);

        return (q->rear - q->front) + 1;
}

static inline void* queue_peek(queue_t *q)
{
        if (queue_is_empty(q))
                return NULL;

        return q->queue[q->front];
}

static inline void queue_enqueue(queue_t *q, void* value)
{
        if (queue_is_full(q)) {
                return;
        } else if (queue_is_empty(q)) {
                q->front++;
        }

        q->rear = (q->rear + 1) % MAX_ARRAY_SIZE;
        q->queue[q->rear] = value;
}

static inline void* queue_dequeue(queue_t *q)
{
        if (queue_is_empty(q))
                return NULL;

        void* temp = q->queue[q->front];

        if (q->front == q->rear) {
                q->front = -1;
                q->rear = -1;
        } else {
                q->queue[q->front++] = NULL;
        }

        return temp;
}

static inline void queue_display(queue_t *q)
{
        if (queue_is_empty(q)) {
                printf("Queue Is Empty\n");
                return;
        }

        for (int i = q->front; i <= q->rear; i++)
                printf("|%p", q->queue[i]);
        printf("|\n");
}

#endif /* QUEUE_H */

