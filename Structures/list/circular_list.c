#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "acutest.h"

struct Node {
        int Data;
        struct Node *Next;
} *tail;

int size = 0;

struct Node* new_node(int data, struct Node *next)
{
        struct Node *node = malloc(sizeof *node);

        node->Data = data;
        node->Next = next;

        return node;
}

void init(int val)
{
        struct Node *p = new_node(val, 0);
        tail = p;
        tail->Next = p;
        size++;
}

int len()
{
        return size;
}


int is_empty()
{
        return (size <= 0);
}

void display()
{
        if (is_empty()) {
                // printf("List Is Empty\n");
                return;
        }
        struct Node *temp = tail->Next;

        while (temp != tail) {
                printf("%d->", temp->Data);
                temp = temp->Next;
        }
        printf("%d\n", temp->Data);
}

void last_deletion()
{
        free(tail);
        tail = 0;

        size--;
}

void insert_beg(int val)
{
        if (is_empty()) {
                init(val);
                return;
        }
        tail->Next = new_node(val, tail->Next);
        size++;
}

void insert_after(int pos, int val)
{
        if (pos <= 0 || pos >= size) {
                pos <= 0 ? insert_beg(val) : insert_end(val);
                return;
        }
        struct Node *temp = tail->Next;

        for (int i = 1; i < pos; i++)
                temp = temp->Next;

        temp->Next = new_node(val, temp->Next);
        size++;
}

void insert_end(int val)
{
        if (is_empty()) {
                init(val);
                return;
        }

        tail->Next = new_node(val, tail->Next);
        tail = tail->Next;
        size++;
}

void delete_first()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        struct Node *temp = tail->Next;
        tail->Next = temp->Next;

        free(temp);

        size--;
}

void delete_node(int pos)
{
        if (pos <= 1 || pos >= size) {
                pos <= 1 ? delete_first() : delete_last();
                return;
        }

        struct Node *prev = tail;
        struct Node *next = tail->Next;

        for (int i = 1; i < pos; i++) {
                prev = next;
                next = next->Next;
        }

        prev->Next = next->Next;

        free(next);

        size--;
}

void delete_last()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } 

        struct Node *prev = tail;

        for (int i = 1; i < size; i++) {
                prev = prev->Next;
        }

        struct Node *temp = tail;

        prev->Next = tail->Next;
        tail = prev;

        free(temp);

        size--;
}


/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_create()
{
        TEST_CHECK(is_empty());
        init(69);
        TEST_CHECK(!is_empty());
        TEST_CHECK(len() == 1);

        if (!TEST_CHECK(tail->Data == 69))
                TEST_MSG("Expected 69 got %d", tail->Data);
}

void test_insert_beg()
{
        init(69);
        
        insert_beg(1);
        TEST_CHECK(tail->Next->Data == 1);

        insert_beg(2);
        TEST_CHECK(tail->Next->Data == 2);
        TEST_CHECK(len() == 3);
}

void test_insert_after()
{
        init(69);

        insert_after(0, 10);
        TEST_CHECK(tail->Next->Data == 10);

        insert_after(len() + 1, 11);
        TEST_CHECK(tail->Data == 11);

        insert_after(1, 3);
        TEST_CHECK(tail->Next->Next->Data == 3);

        insert_after(3, 4);
        TEST_CHECK(tail->Next->Next->Next->Next->Data == 4);
        TEST_CHECK(len() == 5);
}

void test_insert_end()
{
        init(69);

        insert_end(5);
        TEST_CHECK(tail->Data == 5);
        TEST_CHECK(len() == 2);
}

void test_multi_insert()
{
        init(69);

        insert_end(7);
        TEST_CHECK(tail->Data == 7);
        TEST_CHECK(tail->Next->Data == 69);

        insert_beg(8);
        TEST_CHECK(tail->Next->Data == 8);
        TEST_CHECK(tail->Data == 7);

        insert_after(-1, 9);
        TEST_CHECK(tail->Next->Data == 9);
        TEST_CHECK(tail->Data == 7);

        insert_end(10);
        TEST_CHECK(tail->Data == 10);
        TEST_CHECK(tail->Next->Data == 9);

        insert_beg(11);
        TEST_CHECK(tail->Next->Data == 11);
        TEST_CHECK(tail->Next->Next->Data == 9);
        TEST_CHECK(tail->Data == 10);

        insert_after(len(), 12);
        TEST_CHECK(tail->Next->Data == 11);
        TEST_CHECK(tail->Next->Next->Data == 9);
        TEST_CHECK(tail->Data == 12);
}

void test_delete_first()
{
        int MAX = 10;
        int count = 1;

        init(69);

        /* Fill List */
        for (int i = 1; i < MAX; i++) {
                TEST_CHECK(len() == i);
                insert_end(i);
        }

        // init(69)
        TEST_CHECK(tail->Next->Data == 69);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 2);

        TEST_CASE("LAST DELETE");
        while (len() > 0) {
                delete_first();
        }
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_first();
        delete_first();
        TEST_CHECK(len() >= 0);
}

void test_delete_node()
{
        int MAX = 10;
        int count = 1;

        init(69);

        /* Fill List */
        for (int i = 1; i < MAX; i++) {
                TEST_CHECK(len() == i);
                insert_end(i);
        }

        delete_node(0);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 1);
        TEST_CHECK(tail->Next->Next->Data == 2);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 2);
        TEST_CHECK(tail->Next->Next->Data == 3);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(2);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Next->Data == 4);
        TEST_CHECK(tail->Next->Next->Next->Data == 5);
        TEST_CHECK(tail->Data == MAX - 1);
        
        delete_node(-1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 4);
        TEST_CHECK(tail->Next->Next->Data == 5);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(size);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 4);
        TEST_CHECK(tail->Data == MAX - 2);

        delete_node(size + 1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 4);
        TEST_CHECK(tail->Data == MAX - 3);
        
        TEST_CASE("LAST DELETE");
        while (len() > 0) {
                delete_node(count++);
        }
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_node(1);
        delete_node(2);
        TEST_CHECK(len() >= 0);
}

void test_delete_last()
{
        int MAX = 10;
        int count = 1;

        init(69);

        /* Fill List */
        for (int i = 1; i < MAX; i++) {
                TEST_CHECK(len() == i);
                insert_end(i);
        }

        delete_last();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Data == MAX - count);
        
        delete_last();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Data == MAX - count);
        
        TEST_CASE("LAST DELETE");
        while (len() > 0) {
                delete_last();
        }
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_last();
        delete_last();
        TEST_CHECK(len() >= 0);
}

void test_multi_delete()
{
        insert_end(1);
        insert_end(2);
        TEST_CHECK(tail->Data == 2 && tail->Next->Data == 1);
        delete_last();
        TEST_CHECK(tail->Data != 2 && tail->Data == 1);
        
        insert_beg(3);
        TEST_CHECK(tail->Data == 1 && tail->Next->Data == 3);
        delete_first();
        TEST_CHECK(tail->Data != 3 && tail->Data == 1);

        insert_after(1, 5);
        TEST_CHECK(tail->Data == 5 && tail->Next->Data == 1);
        delete_node(2);
        TEST_CHECK(tail->Data != 5 && tail->Data == 1);
}


TEST_LIST = {
        { "CREATE", test_create },

        { "INSERT BEGINNING", test_insert_beg },
        { "INSERT AFTER", test_insert_after },
        { "INSERT END", test_insert_end },
        { "INSERT BEGINNING/AFTER/END", test_multi_insert },

        { "DELETE FIRST", test_delete_first },
        { "DELETE NODE", test_delete_node },
        { "DELETE LAST", test_delete_last },
        { "DELETE FIRST/NODE/LAST", test_multi_delete },

        { NULL, NULL }
};