#ifndef DEQUE_H
#define DEQUE_H

void enqueue_front(int val);
void enqueue_rear(int val);
void dequeue_front();
void dequeue_rear();
int peek();

void display();
int is_full();
int is_empty();
int len();

#endif // !DEQUE_H
