#include <stdio.h>

#include "pqueue.h"
#include "acutest.h"

/* Unordered ascending priority queue */

#define N 20

struct Item {
        int Value;
        int Priority;
};

struct Item queue[N];

// pointer to last inserted item
int ptr  = -1;

int is_full()
{
        return (ptr == N - 1);
}

int is_empty()
{
        return  (ptr <= -1);
}

int len()
{
        if (is_empty()) {
                return 0;
        }

        return ptr + 1;
}

void init()
{
        ptr = -1;
}

int peek()
{
        if (is_empty()) {
                return -1;
        }

        int idx = 0;

        for (int i = 0; i <= ptr; i++) {
                if (queue[i].Priority > queue[idx].Priority) {
                        idx = i;
                }
        }

        return idx;
}

void enqueue(int value, int priority)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        }

        ptr++;
        queue[ptr].Value = value;
        queue[ptr].Priority = priority;
}

void dequeue()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        // shift elements
        for (int i = ptr; i > peek(); i--) {
                queue[i - 1].Value = queue[i].Value;
                queue[i - 1].Priority = queue[i].Priority;
        }

        ptr--;
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

        enqueue(1, 2);
        TEST_CHECK(queue[peek()].Value == 1);
        TEST_CHECK(len() == 1);

        enqueue(2, 3);
        TEST_CHECK(queue[peek()].Value == 2);
        TEST_CHECK(len() == 2);

        enqueue(3, 1);
        TEST_CHECK(queue[peek()].Value == 2);
        TEST_CHECK(len() == 3);

        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                enqueue(69, 0);
        }
        TEST_CHECK(len() <= N);

}

void test_dequeue()
{
        init();

        TEST_CHECK(is_empty());

        enqueue(1, 0);
        TEST_CHECK(queue[peek()].Value == 1);
        TEST_CHECK(len() == 1);

        enqueue(2, 3);

        dequeue();
        TEST_CHECK(queue[peek()].Value == 1);
        TEST_CHECK(len() == 1);

        enqueue(3, 2);

        dequeue();
        TEST_CHECK(queue[peek()].Value == 1);
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
