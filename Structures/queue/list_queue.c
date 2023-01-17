#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "acutest.h"

struct Node {
        int Data;
        struct Node *Next;
} *front, *rear;

int size = 0;
const int CAPACITY = 50;

struct Node* new_node(int val, struct Node* Next)
{
        struct Node* p = malloc(sizeof *p);

        p->Data = val;
        p->Next = Next;

        return p;
}

int is_empty()
{
        return (size <= 0);
}

int is_full()
{
        return (size >= CAPACITY);
}

int len()
{
        return size;
}

int peek()
{
        if (is_empty()) {
                return -1;
        }

        return front->Data;
}

void init()
{
        while (size > 0) {
                dequeue();
                size--;
        }

        front = NULL;
        rear = NULL;
}

void enqueue(int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        } else if (is_empty()) {
                front = new_node(val, 0);
                rear = front;

                size++;
                return;
        }

        struct Node* temp = new_node(val, 0);
        rear->Next = temp;
        rear = temp;

        size++;
}

void dequeue()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        struct Node* temp = front;
        front = temp->Next;

        free(temp);

        size--;
}

void display()
{
        if (is_empty()) {
                printf("Queue Is Empty\n");
                return;
        }

        for (struct Node* temp = front; temp != 0; temp = temp->Next)
                printf("|%d", temp->Data);
        printf("|\n");
}


/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

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
        for (int i = 0; i < CAPACITY + 1; i++) {
                enqueue(69);
        }
        TEST_CHECK(len() <= CAPACITY && size <= CAPACITY);
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
        { "ENQUEUE", test_enqueue },
        { "DEQUEUE", test_dequeue },

        { NULL, NULL }
};
