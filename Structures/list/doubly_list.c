#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "acutest.h"

// NOTE: You can also add a tail pointer to improve time complexity.
struct Node {
        struct Node *Prev;
        int Data;
        struct Node *Next;
} *head;

int size = 0;

struct Node* new_node(struct Node *prev, int val, struct Node* next)
{
        struct Node *node = malloc(sizeof(struct Node));

        node->Prev = prev;
        node->Data = val;
        node->Next = next;

        return node;
}

void init(int val)
{
        head = new_node(0, val, 0);
        size++;
}

int is_empty()
{
        return (size <= 0);
}

int len()
{
        return size;
}

void display()
{
        if (is_empty()) {
                printf("List Is Empty\n");
                return;
        }

        printf("(0x00)");
        for (struct Node *curr = head; curr != 0; curr = curr->Next)
                printf("<-%d->", curr->Data);
        printf("(0x00)\n");
}


void insert_beg(int val)
{
        if (is_empty()) {
                init(val);
                return;
        }

        head->Prev = new_node(0, val, head);
        head = head->Prev;

        size++;
}

void insert_after(int pos, int val)
{
        if (pos <= 0 || pos >= size) {
                pos <= 0 ? insert_beg(val) : insert_end(val);
                return;
        }

        struct Node *curr = head;

        for (int i = 1; i < pos; i++)
                curr = curr->Next;

        curr->Next = new_node(curr, val, curr->Next);
        curr->Next->Next->Prev = curr->Next;

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

        temp->Next = new_node(temp, val, 0);

        size++;
}

void delete_first()
{
        if (is_empty()) {
                // printf("Uderflow Condition\n");
                return;
        } else if (head->Next == 0) {
                free(head);
                // head = 0; /* optional */

                size--;
                return;
        }

        struct Node* temp = head;

        head = head->Next;
        head->Prev = 0;

        free(temp);

        size--;
}

void delete_node(int pos)
{
        if (pos <= 1 || pos >= size) {
                pos <= 1 ? delete_first() : delete_last();
                return;
        }

        struct Node *temp = head;

        for (int i  = 1; i < pos; i++)
                temp = temp->Next;

        temp->Prev->Next = temp->Next;
        temp->Next->Prev = temp->Prev;

        free(temp);

        size--;
}

void delete_last()
{
        if (is_empty()) {
                // printf("Uderflow Condition\n");
                return;
        } else if (head->Next == 0) {
                free(head);
                // head = 0; /* optional */

                size--;
                return;
        }

        struct Node *curr = head;

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
        TEST_CHECK(head->Next->Data == 69);
        TEST_CHECK(head->Data == 1);
        TEST_CHECK(head->Next->Prev->Data == 1);
        TEST_CHECK(len() == 2);

        insert_beg(2);
        TEST_CHECK(head->Next->Data == 1);
        TEST_CHECK(head->Next->Prev->Data == 2);
        TEST_CHECK(head->Next->Next->Data == 69);
        TEST_CHECK(head->Next->Next->Prev->Data == 1);
        TEST_CHECK(len() == 3);
}

void test_insert_after()
{
        init(69);

        insert_after(0, 10);
        TEST_CHECK(head->Data == 10);
        TEST_CHECK(head->Next->Data == 69);
        TEST_CHECK(head->Next->Prev->Data == 10);

        insert_after(size + 1, 11);
        TEST_CHECK(head->Data == 10);
        TEST_CHECK(head->Next->Next->Data == 11);
        TEST_CHECK(head->Next->Next->Prev->Data == 69);

        insert_after(1, 30);
        TEST_CHECK(head->Data == 10);
        TEST_CHECK(head->Next->Data == 30);
        TEST_CHECK(head->Next->Next->Data == 69);
        TEST_CHECK(head->Next->Prev->Data == 10);
        TEST_CHECK(head->Next->Next->Prev->Data == 30);

        insert_after(2, 4);
        TEST_CHECK(head->Data == 10);
        TEST_CHECK(head->Next->Next->Data == 4);
        TEST_CHECK(head->Next->Next->Prev->Data == 30);
        TEST_CHECK(len() == 5);
}

void test_insert_end()
{
        init(69);

        insert_end(5);
        TEST_CHECK(head->Next->Data == 5);
        TEST_CHECK(head->Next->Prev->Data == 69);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(len() == 2);

        insert_end(6);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Data == 5);
        TEST_CHECK(head->Next->Prev->Data == 69);
        TEST_CHECK(head->Next->Next->Data == 6);
        TEST_CHECK(head->Next->Next->Prev->Data == 5);
        TEST_CHECK(len() == 3);

}

void test_multi_insert()
{
        init(69);

        insert_end(7);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Data == 7);

        insert_beg(8);
        TEST_CHECK(head->Data == 8);
        TEST_CHECK(head->Next->Prev->Data == 8);
        TEST_CHECK(head->Next->Data == 69);

        insert_after(-1, 9);
        TEST_CHECK(head->Data == 9);
        TEST_CHECK(head->Next->Data == 8);
        TEST_CHECK(head->Next->Prev->Data == 9);

        insert_end(10);
        TEST_CHECK(head->Next->Next->Next->Next->Data == 10);
        TEST_CHECK(head->Next->Data == 8);
        TEST_CHECK(head->Next->Next->Next->Next->Prev->Data == 7);
        
        insert_beg(11);
        TEST_CHECK(head->Data == 11);
        TEST_CHECK(head->Next->Data == 9);
        TEST_CHECK(head->Next->Prev->Data == 11);

        insert_after(2, 12);
        TEST_CHECK(head->Next->Next->Data == 12);
        TEST_CHECK(head->Next->Next->Prev->Data == 9);
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
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Prev->Data == 69);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 1);
        TEST_CHECK(head->Next->Data == 2);
        TEST_CHECK(head->Next->Prev->Data == 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 2);
        TEST_CHECK(head->Next->Data == 3);
        TEST_CHECK(head->Next->Prev->Data == 2);

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
        TEST_CHECK(head->Data == 1);
        TEST_CHECK(head->Next->Prev->Data == 1);
        TEST_CHECK(head->Next->Data == 2);
        
        delete_node(1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 2);
        TEST_CHECK(head->Next->Prev->Data == 2);
        TEST_CHECK(head->Next->Data == 3);

        delete_node(2);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Next->Data == 4);
        TEST_CHECK(head->Next->Prev->Data == 2);
        
        delete_node(-1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data == 4);
        TEST_CHECK(head->Next->Data == 5);
        TEST_CHECK(head->Next->Prev->Data == 4);

        delete_node(size);
        TEST_CHECK(len() == MAX - count++);

        delete_node(size + 1);
        TEST_CHECK(len() == MAX - count++);

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
        init(69);

        insert_end(1);
        insert_end(2);
        TEST_CHECK(len() == 3);

        delete_last();
        TEST_CHECK(len() == 2);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Prev->Data == 69);
        TEST_CHECK(head->Next->Data == 1);

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
        TEST_CHECK(len() == 3);

        delete_last();
        TEST_CHECK(len() == 2);
        TEST_CHECK(head->Data == 69);
        TEST_CHECK(head->Next->Prev->Data == 69);
        TEST_CHECK(head->Next->Data == 1);

        insert_beg(3);
        TEST_CHECK(head->Data == 3);
        TEST_CHECK(head->Next->Data == 69);
        delete_first();
        TEST_CHECK(head->Data == 69 && head->Next->Data == 1);

        insert_after(1, 4);
        TEST_CHECK(head->Data == 69 && head->Next->Data == 4);
        delete_node(1);
        TEST_CHECK(head->Data == 4 && head->Next->Data == 1);
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
        { "DELETE /FIRST/NODE/LAST", test_multi_delete },

        { NULL, NULL }
};
