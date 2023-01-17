#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "acutest.h"

struct Node {
        int Data;
        struct Node *Next;
} *top;

int size = 0; 

struct Node* new_node(int value, struct Node* next)
{
        struct Node *p = malloc(sizeof *p);

        p->Data = value;
        p->Next = next;

        return p;
}

int is_empty()
{
        return (size <= 0);
}

int len()
{
        return size;
}

void init()
{
        top = NULL;
        size = 0;
}

int peek()
{
        if (!top) {
                // printf("Stack is empty\n");
                return 0;
        }

        return top->Data;
}

void push(int value)
{
        top = new_node(value, top);
        size++;
}

void pop()
{
        if (size <= 0) {
                // printf("Stack Underflow\n");
                return;
        }
        struct Node *tmp = top;

        top = top->Next;
        free(tmp);
        size--;
}

void display()
{
        if (!top) {
                // printf("Stack is empty\n");
                return;
        }
        struct Node *tmp = top;

        while (tmp != 0) {
                printf("|\t%d\t|\n", tmp->Data);
                tmp = tmp->Next;
        }
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

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
        { "PUSH", test_push },
        { "POP", test_pop },

        { NULL, NULL }
};
