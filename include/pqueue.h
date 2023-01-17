#ifndef PQUEUE_H
#define PQUEUE_H

void enqueue(int value, int priority);
void dequeue();
int peek();

void display();
int is_full();
int is_empty();
int len();

#endif // PQUEUE_H
