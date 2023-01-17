#include <stdio.h>

#include "queue.h"
#include "acutest.h"

#define N 20

int queue[N];
int rear = -1;
int front = -1;

int is_full()
{
        return ((rear + 1) % N == front);
}

int is_empty()
{
        return (rear <= -1 && front <= -1);
}

int len()
{
        if (is_empty())
                return 0;

        if (rear < front)
                return (N - front) + (rear + 1);

        return (rear - front) + 1;
}

void init()
{
        front = -1;
        rear = -1;
}

int peek()
{
        if (is_empty()) {
                return -1;
        }

        return queue[front];
}

void enqueue(int value)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        } else if (is_empty()) {
                front++;
        } 

        rear = (rear + 1) % N;
        queue[rear] = value;
}

void dequeue()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (front == rear) {
                front = -1;
                rear = -1;
                return;
        }
        front++;
}

void display()
{
        if (is_empty()) {
                printf("Queue Is Empty\n");
                return;
        }

        for (int i = front; i != rear; ) {
                printf("|%d", queue[i]);
                i = (i + 1) % N;
        }
        printf("|%d|\n", queue[rear]);
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_min_size()
{
        TEST_CHECK(N > 10);
        TEST_MSG("N MUST BE GREATER THAN `10` TO EXECUTE TESTS");
}

void test_enqueue()
{
        init();

        TEST_CHECK(is_empty());

        enqueue(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue(2);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 2);

        enqueue(3);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 3);

        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                enqueue(69);
        }
        TEST_CHECK(len() <= N);

}

void test_dequeue()
{
        init();

        TEST_CHECK(is_empty());

        enqueue(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue(2);

        dequeue();
        TEST_CHECK(peek() == 2);
        TEST_CHECK(len() == 1);

        enqueue(3);

        dequeue();
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 1);

        dequeue();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        dequeue();
        TEST_CHECK(len() == 0);
}

TEST_LIST = {
        { "QUEUE SIZE", test_min_size },

        { "ENQUEUE", test_enqueue },
        { "DEQUEUE", test_dequeue },

        { NULL, NULL }
};
