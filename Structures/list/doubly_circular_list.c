#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "acutest.h"

struct Node {
        struct Node* Prev;
        int Data;
        struct Node* Next;
} *tail;

int size = 0;

struct Node* new_node(struct Node* prev, int val, struct Node* next)
{
        struct Node *node = malloc(sizeof(struct Node));

        node->Prev = prev;
        node->Data = val;
        node->Next = next;

        return node;
}

int is_empty()
{
        return (size <= 0);
}

int len()
{
        return size;
}

void init(int val)
{
        tail = new_node(0, val, 0);
        tail->Prev = tail;
        tail->Next = tail;
        size++;
}


void display()
{
        if (is_empty()) {
                printf("List Is Empty\n");
                return;
        }
        struct Node *curr = tail->Next;

        printf("(%d)", tail->Data);
        for (int i = 0; i < size; i++) {
                printf("<-%d->", curr->Data);
                curr = curr->Next;
        }
        printf("(%d)\n", curr->Data);
}

void insert_beg(int val)
{
        struct Node *node = new_node(tail, val, tail->Next);

        tail->Next->Prev = node;
        tail->Next = node;

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

        temp->Next = new_node(temp, val, temp->Next);
        temp->Next->Next->Prev = temp->Next;

        size++;
}

void insert_end(int val)
{
        if (is_empty()) {
                init(val);
                return;
        }

        struct Node *node = new_node(tail, val, tail->Next);

        // Update Head
        tail->Next->Prev = node;

        // Update current tail to new tail
        tail->Next = node;
        tail = node;

        size++;
}

void delete_first()
{
        if (is_empty()) {
                return;
        }

        struct Node *head = tail->Next;
        tail->Next = head->Next;

        head->Next->Prev = tail;
        
        free(head);

        size--;
}

void delete_node(int pos)
{
        if (pos <= 1 || pos >= size) {
                pos <= 1 ? delete_first() : delete_last();
                return;
        }

        struct Node *temp = tail->Next;

        for (int i = 1; i < pos; i++) {
                temp = temp->Next;
        }

        temp->Next->Prev = temp->Prev;
        temp->Prev->Next = temp->Next;

        free(temp);

        size--;
}

void delete_last()
{
        if (is_empty())
                return;

        struct Node *target = tail;

        tail->Prev->Next = tail->Next;
        tail = tail->Prev;
        
        // Update head
        tail->Next->Prev = tail;

        free(target);

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
        TEST_CHECK(tail->Next->Next->Data == 69);
        TEST_CHECK(tail->Next->Prev->Data == tail->Data);
        TEST_CHECK(len() == 2);

        insert_beg(2);
        TEST_CHECK(tail->Next->Data == 2);
        TEST_CHECK(tail->Next->Prev->Data == 69);
        TEST_CHECK(tail->Prev->Data == 1);
        TEST_CHECK(tail->Prev->Prev->Data == 2);
        TEST_CHECK(len() == 3);
}

void test_insert_after()
{
        init(69);

        insert_after(0, 10);
        TEST_CHECK(tail->Data == 69);
        TEST_CHECK(tail->Next->Data == 10);
        TEST_CHECK(tail->Next->Prev->Data == tail->Data);

        insert_after(len() + 1, 11);
        TEST_CHECK(tail->Data == 11);
        TEST_CHECK(tail->Prev->Data == 69);
        TEST_CHECK(tail->Prev->Prev->Data == 10);

        insert_after(1, 30);
        TEST_CHECK(tail->Data == 11);
        TEST_CHECK(tail->Next->Next->Data == 30);
        TEST_CHECK(tail->Next->Next->Prev->Data == 10);

        insert_after(2, 4);
        TEST_CHECK(tail->Data == 11);
        TEST_CHECK(tail->Next->Next->Next->Data == 4);
        TEST_CHECK(tail->Next->Next->Next->Prev->Data == 30);
        TEST_CHECK(tail->Prev->Data == 69);
        TEST_CHECK(tail->Prev->Prev->Data == 4);
        TEST_CHECK(len() == 5);
}

void test_insert_end()
{
        init(69);

        insert_end(5);
        TEST_CHECK(tail->Data == 5);
        TEST_CHECK(tail->Next->Prev->Data == 5);
        TEST_CHECK(tail->Next->Data == 69);
        TEST_CHECK(tail->Prev->Data == 69);
        TEST_CHECK(tail->Next->Next->Data == 5);
        TEST_CHECK(len() == 2);

        insert_end(6);
        TEST_CHECK(tail->Data == 6);
        TEST_CHECK(tail->Next->Prev->Data == 6);
        TEST_CHECK(tail->Prev->Data == 5);
        TEST_CHECK(tail->Prev->Next->Data == 6);
        TEST_CHECK(tail->Prev->Prev->Data == 69);
        TEST_CHECK(tail->Next->Next->Data == 5);
        TEST_CHECK(len() == 3);

}

void test_multi_insert()
{
        init(69);

        insert_end(7);
        TEST_CHECK(tail->Data == 7);
        TEST_CHECK(tail->Prev->Data == 69);

        insert_beg(8);
        TEST_CHECK(tail->Next->Data == 8);
        TEST_CHECK(tail->Next->Prev->Data == 7);

        insert_after(-1, 9);
        TEST_CHECK(tail->Next->Data == 9);
        TEST_CHECK(tail->Next->Next->Data == 8);
        TEST_CHECK(tail->Next->Prev->Data == 7);

        insert_end(10);
        TEST_CHECK(tail->Data == 10);
        TEST_CHECK(tail->Prev->Data == 7);
        TEST_CHECK(tail->Next->Data == 9);
        TEST_CHECK(tail->Next->Prev->Data == 10);
        TEST_CHECK(tail->Prev->Next->Data == 10);
        
        insert_beg(11);
        TEST_CHECK(tail->Data == 10);
        TEST_CHECK(tail->Next->Data == 11);
        TEST_CHECK(tail->Next->Prev->Data == 10);
        TEST_CHECK(tail->Next->Next->Data == 9);
        TEST_CHECK(tail->Next->Next->Prev->Data == 11);

        insert_after(2, 12);
        TEST_CHECK(tail->Next->Next->Next->Data == 12);
        TEST_CHECK(tail->Next->Next->Next->Prev->Data == 9);
}

void test_delete_first()
{
        int MAX = 100;
        int count = 1;

        init(69);

        /* Fill List */
        for (int i = 1; i < MAX; i++) {
                TEST_CHECK(len() == i);
                insert_end(i);
        }

        // init(69)
        TEST_CHECK(tail->Next->Data == 69);
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 1);
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 2);
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);
        TEST_CHECK(tail->Data == MAX - 1);

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
        int MAX = 100;
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
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 2);
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(2);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Next->Data == 4);
        TEST_CHECK(tail->Next->Next->Prev->Data == 2);
        TEST_CHECK(tail->Data == MAX - 1);
        
        delete_node(-1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Next->Data == 4);
        TEST_CHECK(tail->Next->Prev->Data == MAX - 1);
        TEST_CHECK(tail->Data == MAX - 1);

        delete_node(size);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Data == MAX - 2);
        TEST_CHECK(tail->Prev->Data == MAX - 3);

        delete_node(size + 1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(tail->Data == MAX - 3);
        TEST_CHECK(tail->Prev->Data == MAX - 4);


        TEST_CASE("LAST DELETE");
        while (len() > 0) {
                delete_node(0);
        }
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_node(1);
        delete_node(2);
        TEST_CHECK(len() >= 0);
}

void test_delete_last()
{
        int MAX = 100;
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
        TEST_CHECK(tail->Prev->Data == MAX - count - 1);
        TEST_CHECK(tail->Next->Data == 69);
        TEST_CHECK(tail->Next->Prev->Data == tail->Data);

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
        TEST_CHECK(tail->Data == 2);
        delete_last();
        TEST_CHECK(tail->Data == 1);
        
        insert_beg(3);
        TEST_CHECK(tail->Data == 1);
        TEST_CHECK(tail->Next->Data == 3);
        delete_first();
        TEST_CHECK(tail->Data == 1 && tail->Next->Data == 1);

        insert_after(1, 4);
        TEST_CHECK(tail->Data == 4 && tail->Next->Data == 1);
        delete_node(1);
        TEST_CHECK(tail->Data == 4 && tail->Next->Data == 4);
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
