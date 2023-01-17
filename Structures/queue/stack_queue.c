#include <stdio.h>

#include "queue.h"
#include "acutest.h"

#define N 20

int stack[N];
int temp_stack[N];
int top = -1;

/* ************* Stack Operations ************* */
void push(int value)
{
        stack[++top] = value;
}

int pop()
{
        return stack[top--];
}

/* ************* Queue ************* */
int is_empty()
{
        return (top <= -1);
}

int is_full()
{
        return (top >= N - 1);
}

int len()
{
        return (top + 1);
}

void init()
{
        top = -1;
}

int peek()
{
        if (is_empty()) {
                return -1;
        }

        return stack[0];
}

void enqueue(int value)
{
        if (is_full()) {
                // printf("Overflow Condition");
                return;
        }

        push(value);
}

void dequeue()
{ 
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        int temp_top = -1;
        int new_size = top - 1;

        while (top > -1) {
                temp_stack[++temp_top] = pop();
        }
        temp_top--;

        while (top < new_size)
                push(temp_stack[temp_top--]);        
}

void display()
{
        if (is_empty()) {
                printf("Queue is Empty\n");
                return;
        }

        for (int i = 0; i <= top; i++)
                printf("|%d", stack[i]);
        printf("|\n");
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
