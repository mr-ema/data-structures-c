#include <stdio.h>

#include "stack.h"
#include "acutest.h"

#define N 20

int stack[N];
int top = -1;

int is_empty()
{
        return (top < 0);
}

int len()
{
        return top + 1;
}

void init()
{
        top = -1;
}

int peek()
{
        return stack[top];
}

void push(int val)
{
        if (len() >= N) {
                // printf("Stack Overflow\n");
                return;
        }

        top++;
        stack[top] = val;
}

void pop()
{
        if (top < 0) {
                // printf("Stack Underflow\n");
                return;
        }

        top--;
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_min_size()
{
        TEST_CHECK(N > 10);
        TEST_MSG("N MUST BE GREATER THAN `10` TO EXECUTE TESTS");
}

void test_push()
{
        init();

        TEST_CHECK(is_empty());

        push(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        push(2);
        TEST_CHECK(peek() == 2);
        TEST_CHECK(len() == 2);

        push(3);
        TEST_CHECK(peek() == 3);
        TEST_CHECK(len() == 3);

        TEST_CASE("OVERFLOW");
        for (int i = 0; i < N + 1; i++) {
                push(69);
        }
        TEST_CHECK(len() <= N);

}

void test_pop()
{
        init();

        TEST_CHECK(is_empty());

        push(1);
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        push(2);

        pop();
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        push(3);

        pop();
        TEST_CHECK(peek() == 1);
        TEST_CHECK(len() == 1);

        pop();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        pop();
        TEST_CHECK(len() == 0);
}

TEST_LIST = {
        { "STACK SIZE", test_min_size },

        { "PUSH", test_push },
        { "POP", test_pop },

        { NULL, NULL }
};
