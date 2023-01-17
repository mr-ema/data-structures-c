#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "acutest.h"

struct Node {
        int Data;
        struct Node* Next;
} *head;

int size = 0;

int len()
{
        return size;
}

int is_empty()
{
        return (size <= 0);
}

struct Node* new_node(int val, struct Node *next)
{
        struct Node* node = malloc(sizeof(struct Node));

        node->Data = val;
        node->Next = next;

        return node;
}

/* Initialize list */
void init(int val)
{
        head = new_node(val, 0);

        size++;
}

void display()
{
        if (is_empty()) {
                // printf("List is empty\n");
                return;
        }

        struct Node* temp = head;

        while (temp != 0) {
                printf("[%d]->", temp->Data);
                temp = temp->Next;
        } printf("(0x00)\n");
}

void insert_beg(int val)
{
        if (is_empty()) {
                init(val);
                return;
        }

        head = new_node(val, head);

        size++;
}

void insert_after(int pos, int val)
{
        if (pos <= 0 || pos >= size) {
                pos <= 0 ? insert_beg(val) : insert_end(val);
                return;
        }

        struct Node* temp = head;

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

        struct Node* temp = head;

        while (temp->Next != 0)
                temp = temp->Next;

        temp->Next = new_node(val, 0);

        size++;
}

void delete_first()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (head->Next == 0) {
                free(head);
                // head = 0; /* Optional */

                size--;
                return;
        }

        struct Node* temp = head;
        head = temp->Next;

        free(temp);
        size--;
}

void delete_node(int pos)
{
        if (pos <= 1 || pos >= size) {
                pos <= 1 ? delete_first() : delete_last();
                return;
        } 

        struct Node *curr, *prev;
        curr = head;

        for (int i = 1; i < pos; i++) {
                prev = curr;
                curr = curr->Next;
        }

        prev->Next = curr->Next;
        free(curr);

        size--;
}

void delete_last()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (head->Next == 0) {
                free(head);
                // head = 0; /* Optional */

                size--;
                return;
        }

        struct Node* curr = head;

        while (curr->Next->Next != 0) {
                curr = curr->Next;
        }

        free(curr->Next);
        curr->Next = 0;

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

        if (!TEST_CHECK(head->Data == 69))
                TEST_MSG("Expected 69 got %d", head->Data);
}

void test_insert_beg()
{
        init(69);

        insert_beg(1);
        TEST_CHECK(head->Data == 1);

        insert_beg(2);
        TEST_CHECK(head->Data == 2);
        TEST_CHECK(head->Next->Data == 1);
        TEST_CHECK(len() == 3);
}

void test_insert_after()
{
        init(69);

        insert_after(0, 10);
        TEST_CHECK(head->Data == 10);
        TEST_CHECK(head->Next->Data == 69);

        insert_after(len() + 1, 11);
        TEST_CHECK(head->Next->Next->Data == 11);

        insert_after(1, 3);
        TEST_CHECK(head->Next->Data == 3);

        insert_after(3, 4);
        TEST_CHECK(head->Next->Next->Next->Data == 4);
        TEST_CHECK(len() == 5);
}

void test_insert_end()
{
        init(69);

        insert_end(5);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Data == 5);
        TEST_CHECK(len() == 2);
}

void test_multi_insert()
{
        init(69);

        insert_end(7);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Data == 7);

        insert_beg(8);
        TEST_CHECK(head->Data == 8);
        TEST_CHECK(head->Next->Data == 69);

        insert_after(-1, 9);
        TEST_CHECK(head->Data == 9);
        TEST_CHECK(head->Next->Data == 8);

        insert_end(10);
        TEST_CHECK(head->Data == 9);
        TEST_CHECK(head->Next->Next->Next->Next->Data == 10);

        insert_beg(11);
        TEST_CHECK(head->Data == 11);
        TEST_CHECK(head->Next->Data == 9);
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
        TEST_CHECK(head->Data == 69);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 2);

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
        TEST_CHECK(head->Data == 1);
        TEST_CHECK(head->Next->Data == 2);

        delete_node(1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 2);
        TEST_CHECK(head->Next->Data == 3);

        delete_node(2);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Next->Data == 4);
        TEST_CHECK(head->Next->Next->Data == 5);
        
        delete_node(-1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 4);
        TEST_CHECK(head->Next->Data == 5);

        delete_node(size);
        TEST_CHECK(len() == MAX - count++);

        delete_node(size + 1);
        TEST_CHECK(len() == MAX - count++);
        
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
        init(69);

        insert_end(1);
        insert_end(2);
        TEST_CHECK(len() == 3);

        delete_last();
        TEST_CHECK(len() == 2);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Data == 1);
        
        delete_last();
        TEST_CHECK(len() == 1);
        TEST_CHECK(head->Data == 69);
        
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
        init(69);

        insert_end(1);
        insert_end(2);
        TEST_CHECK(head->Data == 69 && head->Next->Data == 1);
        delete_last();
        TEST_CHECK(head->Data == 69 && head->Next->Data == 1);
        
        insert_beg(3);
        TEST_CHECK(head->Data == 3 && head->Next->Data == 69);
        delete_first();
        TEST_CHECK(head->Data == 69 && head->Next->Data == 1);

        insert_after(1, 5);
        TEST_CHECK(head->Data == 69 && head->Next->Data == 5);
        delete_node(2);
        TEST_CHECK(head->Data == 69 && head->Next->Data == 1);
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
