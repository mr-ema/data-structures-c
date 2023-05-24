#include <stdio.h>

#define CAPACITY 20

int queue[CAPACITY];
int rear = -1;
int front = 0;


int queue_is_empty() {
        return (rear <= -1 && front <= 0);
}

int queue_is_full() {
        return (rear >= CAPACITY - 1);
}

int queue_len() {
        if (queue_is_empty())
                return 0;

        return (rear - front) + 1;
}

int queue_peek() {
        if (queue_is_empty()) {
                return -1;
        }

        return queue[front];
}

void queue_enqueue(int value) {
        if (queue_is_full()) {
                printf("Overflow Condition\n");
                return;
        }

        queue[++rear] = value;
}

int queue_dequeue() {
        if (queue_is_empty()) {
                printf("Underflow Condition\n");
                return -1;
        } else if (front == rear) {
                int temp = queue[front];

                // reset the queue and return the dequeued element
                front = 0;
                rear  = -1;
                return temp;
        }

        return queue[front++];
}

void queue_display() {
        if (queue_is_empty()) {
                printf("Queue Is Empty\n");
                return;
        }

        for (int i = front; i <= rear; i++)
                printf("|%d", queue[i]);
        printf("|\n");
}

int main() {
        // Enqueue elements
        queue_enqueue(10);
        queue_enqueue(20);
        queue_enqueue(30);

        // Display the queue
        printf("Queue: ");
        queue_display();

        // Peek at the front element
        int front_element = queue_peek();
        printf("Front element: %d\n", front_element);

        // Dequeue elements
        queue_dequeue();
        queue_dequeue();

        // Display the queue after dequeue
        printf("Queue after dequeue: ");
        queue_display();

        // Enqueue more elements
        queue_enqueue(40);
        queue_enqueue(50);

        // Display the queue
        printf("Queue: ");
        queue_display();

        // Dequeue all elements
        while (!queue_is_empty()) {
            queue_dequeue();
        }

        // Display the queue after dequeue
        printf("Queue after dequeue: ");
        queue_display();

        return 0;
}

