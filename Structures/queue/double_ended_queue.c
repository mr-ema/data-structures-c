#include <stdio.h>

#include "deque.h"
#include "acutest.h"

#define N 20

int deque[N];
int front = -1;
int rear = -1;

int is_empty()
{
        return (front <= -1 || rear <= -1);
}

int is_full()
{
        return ((rear + 1) % N == front);
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

        return deque[front];
}

void first_insert(int val)
{
        front = 0;
        rear = 0;
        deque[0] = val;
}

void enqueue_front(int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        } else if (is_empty()) {
                first_insert(val);
                return;
        }
        
        // set front to last index once front reach first index
        front = front == 0 ? N - 1 : front - 1; 
        deque[front] = val;
}

void enqueue_rear(int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        } else if (is_empty()) {
                first_insert(val);
                return;
        }

        // reset rear to 0, once rear reach last index
        rear = (rear + 1) % N; 
        deque[rear] = val;
}

void dequeue_front()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (rear == front) {
                rear = -1;
                front = -1;
                return;
        }

        // Move pointer to the right in a circular manner
        front = (front + 1) % N;
}

void dequeue_rear()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (rear == front) {
                rear = -1;
                front = -1;
                return;
        }
        
        // Move pointer to the left in a circular manner
        rear = rear == 0 ? N - 1 : rear - 1;
}

void display()
{
        if (is_empty()) {
                // printf("Not Elements In Queue\n");
                return;
        }

        for (int i = front; i != rear; ) {
                printf("|%d", deque[i]);
                i = (i + 1) % N;
        }
        printf("|%d|\n", deque[rear]);
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_min_size()
{
        TEST_CHECK(N > 10);
        TEST_MSG("N MUST BE GREATER THAN `10` TO EXECUTE TESTS");
}

void test_enqueue_front()
{
        init();

        TEST_CHECK(is_empty());

        enqueue_front(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_front(2);
        TEST_CHECK(peek() == 2);
        TEST_CHECK(len() == 2);

        enqueue_front(3);
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 3);

        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                enqueue_front(69);
        }
        TEST_CHECK(len() <= N);
}

void test_enqueue_rear()
{
        init();

        TEST_CHECK(is_empty());

        enqueue_rear(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_rear(2);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 2);

        enqueue_rear(3);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 3);

        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                enqueue_rear(69);
        }
        TEST_CHECK(len() <= N);
}

void test_multi_enqueue()
{
        init();

        TEST_CHECK(is_empty());

        enqueue_rear(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_front(2);
        TEST_CHECK(peek() == 2);
        TEST_CHECK(len() == 2);

        enqueue_front(3);
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 3);

        enqueue_rear(4);
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 4);
        
        enqueue_rear(5);
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 5);
        
        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                enqueue_rear(69);
        }
        TEST_CHECK(len() <= N);
}

void test_dequeue_front()
{
        init();

        TEST_CHECK(is_empty());

        enqueue_front(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_front(2);

        dequeue_front();
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_front(3);

        dequeue_front();
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);
        
        enqueue_rear(4);

        dequeue_front();
        TEST_CHECK(peek() == 4);
        TEST_CHECK(len() == 1);

        enqueue_front(5);
        enqueue_rear(6);
        enqueue_front(7);

        dequeue_front();
        TEST_CHECK(peek() == 5);
        TEST_CHECK(len() == 3);

        dequeue_front();
        TEST_CHECK(peek() == 4);
        TEST_CHECK(len() == 2);

        dequeue_front();
        TEST_CHECK(peek() == 6);
        TEST_CHECK(len() == 1);

        dequeue_front();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        dequeue_front();
        TEST_CHECK(len() == 0);
}

void test_dequeue_rear()
{
        init();

        TEST_CHECK(is_empty());

        enqueue_front(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        enqueue_front(2);

        dequeue_rear();
        TEST_CHECK(peek() == 2);
        TEST_CHECK(len() == 1);

        enqueue_front(3);

        dequeue_rear();
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 1);
        
        enqueue_rear(4);

        dequeue_rear();
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 1);

        enqueue_front(5);
        enqueue_rear(6);
        enqueue_front(7);

        dequeue_rear();
        TEST_CHECK(peek() == 7);
        TEST_CHECK(len() == 3);

        dequeue_rear();
        TEST_CHECK(peek() == 7);
        TEST_CHECK(len() == 2);

        dequeue_rear();
        TEST_CHECK(peek() == 7);
        TEST_CHECK(len() == 1);

        dequeue_rear();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        dequeue_rear();
        TEST_CHECK(len() == 0);
}

void test_multi_delete()
{
}

TEST_LIST = {
        { "QUEUE SIZE", test_min_size },

        { "ENQUEUE FRONT", test_enqueue_front },
        { "ENQUEUE REAR", test_enqueue_rear },
        { "ENQUEUE FRONT/REAR", test_multi_enqueue },

        { "DEQUEUE FRONT", test_dequeue_front },
        { "DEQUEUE REAR", test_dequeue_rear },
        { "DEQUEUE FRONT/REAR", test_multi_delete },

        { NULL, NULL }
};
