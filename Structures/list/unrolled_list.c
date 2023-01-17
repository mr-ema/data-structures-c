#include <stdlib.h>

#include "list.h"
#include "acutest.h"

#define CAPACITY 20

int const THRESHOLD = (CAPACITY/2) + 1;

/* Notes:
 *    Much of the code can be optimized.
 *
 *    For example you could avoid reverse
 *    the array in insert_end operation,
 *    if you insert the elements in acending
 *    order.
 *
 *    I will optimized and clean the code
 *    but for now I wanna continue and pass
 *    to the next data structure (trees). */

struct Node {
        int Len;
        int Data[CAPACITY];
        struct Node *Next;
} *head, *tail;

int size = 0;

struct Node* new_node(int val, struct Node *next)
{
        struct Node *node = malloc(sizeof *node);

        node->Data[0] = val;
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

int there_is_space(struct Node *node)
{
        return (node->Len < CAPACITY);
}

void shift_right(int *arr, int start, int end)
{
        if (!(start >= 0 && end < CAPACITY)) {
                printf("ERR_SHIFT_RIGHT -> INVALID ARGUMENT\n");
                return;
        }

        for (int i = end; i > start; i--) {
                arr[i] = arr[i - 1];
        }
}

void shift_left(int *arr, int start, int end)
{
        if (!(start < CAPACITY && end >= 0)) {
                printf("ERR_SHIFT_LEFT -> INVALID ARGUMENT\n");
                return;
        }

        for (int i = end; i < start; i++) {
                arr[i] = arr[i + 1];
        }
}

void swap(int *arr, int first_elem, int second_elem)
{
        if (!(first_elem < CAPACITY && first_elem >= 0 ) && !(second_elem < CAPACITY && second_elem >= 0)) {
                printf("ERR_SWAP -> INVALID ARGUMENT\n");
                return;
        }

        int temp = arr[first_elem];
        
        arr[first_elem] = arr[second_elem];
        arr[second_elem] = temp;
}

void init(int val)
{
        head = new_node(val, 0);
        head->Len++;
        tail = head;

        size++;
}

void display()
{
        if (is_empty()) {
                printf("List Is Empty\n");
                return;
        }

        struct Node *temp = head;

        printf("|");
        while (temp != 0) {
                for (int i = 0; i < temp->Len; i++) {
                        printf(" %d |", temp->Data[i]);
                }

                temp = temp->Next;
                printf(" -> |");
        }
        printf(" NULL |");
}

void insert_beg(int val) {
        if (there_is_space(head)) {
                shift_right(head->Data, 0, head->Len);

                head->Data[0] = val;
                head->Len++;
                size++;

                return;
        }

        head = new_node(val, head);
        head->Len++;
        size++;
        
        while (head->Len != THRESHOLD) {
                head->Data[head->Len] = head->Next->Data[0];
                shift_left(head->Next->Data, head->Next->Len - 1, 0);

                head->Next->Len--;
                head->Len++;
        }
}

void insert_after(int pos, int val)
{
        if (pos <= 0 || pos >= size) {
                pos <= 0 ? insert_beg(val) : insert_end(val);
                return;
        } 

        struct Node *temp = head;

        for (int i = temp->Len; i < pos; ) {
                temp = temp->Next;
                i += temp->Len;
        }

        if (there_is_space(temp)) {
                shift_right(temp->Data, pos, temp->Len);
                temp->Data[pos] = val;

                temp->Len++;
                size++;

                return;
        }

        temp->Next = new_node(0, 0);

        while (temp->Next->Len != THRESHOLD) {
                temp->Next->Data[tail->Next->Len] = temp->Data[tail->Len - 1];

                temp->Next->Len++;
                temp->Len--;
        }

        /* THIS WILL REVERSE THE NEW NODE ARRAY.
         * HOWEVER THIS IS EXPENSIVE TO AVOID THIS
         * YOU COULD START ADDING FROM THRESHOLD
         * WHICH WILL KEEP ORDER OF THE ELEMENTS.
         * BUT I THINK THIS IS MORE READABLE */
        for (int i = 0; i < temp->Next->Len; i++) {
                if (i == (temp->Next->Len - i) - 1) {
                        break;
                }
                swap(temp->Next->Data, i, (temp->Next->Len - i) - 1);
        }

        insert_after(pos, val);
}

void insert_end(int val)
{
        if (there_is_space(tail)) {
                tail->Data[tail->Len] = val;
                tail->Len++;
                size++;

                return;
        }

        tail->Next = new_node(val, 0);
        tail->Next->Len++;
        size++;

        while (tail->Next->Len != THRESHOLD) {
                tail->Next->Data[tail->Next->Len] = tail->Data[tail->Len - 1];

                tail->Next->Len++;
                tail->Len--;
        }

        /* THIS WILL REVERSE THE NEW NODE ARRAY.
         * HOWEVER THIS IS EXPENSIVE TO AVOID THIS
         * YOU COULD START ADDING FROM THRESHOLD
         * WHICH WILL KEEP ORDER OF THE ELEMENTS.
         * BUT I THINK THIS IS MORE READABLE */
        for (int i = 0; i < tail->Next->Len; i++) {
                if (i == (tail->Next->Len - i) - 1) {
                        break;
                }
                swap(tail->Next->Data, i, (tail->Next->Len - i) - 1);
        }

        tail = tail->Next;
}

void delete_first()
{
        if (is_empty()) {
                return;
        } else if (head->Len == 1) {
                struct Node *temp = head;
                head = head->Next;

                free(temp);
                size--;

                return;
        }

        shift_left(head->Data, head->Len, 0);

        head->Len--;
        size--;
}

void delete_node(int pos)
{
        if (pos >= size || pos <= 1) {
                pos <= 1 ? delete_first() : delete_last();
                return;
        }

        struct Node *temp = head;

        for (int i = temp->Len; i < pos; ) {
                temp = temp->Next;
                i += temp->Len;
        }

        shift_left(temp->Data, temp->Len, pos - 1);

        temp->Len--;
        size--;
}

void delete_last()
{
        if (is_empty()) {
                return;
        }
        if (tail->Len > 1) {
                tail->Len--;

                size--;
                return;
        }
        if (head == tail) {
                free(tail);
                head = 0;
                tail = 0;

                size--;
                return;
        }

        struct Node *temp = head;

        while (temp->Next->Next != 0) {
                temp = temp->Next;
        }

        temp->Next = 0;

        free(tail);
        tail = temp;

        size--;
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_basic()
{
        TEST_CHECK(CAPACITY > 5);
        TEST_MSG("CAPACITY must be greater than 5");

        TEST_CHECK(THRESHOLD == (CAPACITY/2)+1);
        TEST_MSG("Expected %d got %d", (CAPACITY/2)+1, THRESHOLD);
}

void test_create()
{
        TEST_CHECK(is_empty());
        init(69);
        TEST_CHECK(!is_empty());
        TEST_CHECK(len() == 1);

        if (!TEST_CHECK(head->Data[0] == 69))
                TEST_MSG("Expected 69 got %d", head->Data[0]);
}

void test_insert_beg()
{
        int i = 0;

        init(69);

        insert_beg(++i);
        TEST_CHECK(head->Data[0] == i);

        insert_beg(++i);
        TEST_CHECK(head->Data[0] == i);
        TEST_CHECK(head->Data[1] == i - 1);
        TEST_CHECK(len() == 3);

        while (len() != CAPACITY + 1) {
                insert_beg(++i);

                if (!TEST_CHECK(i < CAPACITY + 1)) {
                        TEST_MSG("YOU FORGOT INCREASE THE SIZE");
                        break;
                }
        }

        TEST_CHECK(head->Data[0] == i);
        TEST_CHECK(head->Data[1] == i - 1);
        TEST_CHECK(head->Next->Data[head->Next->Len - 1] == 69);
        TEST_CHECK(head->Next->Data[0] == i - THRESHOLD);
        TEST_CHECK(head->Len == THRESHOLD);

        // display();
}

void test_insert_after()
{
        int i = 0;

        init(69);

        insert_after(0, ++i);
        TEST_CHECK(head->Data[0] == i);
        TEST_CHECK(head->Data[1] == 69);
        TEST_CHECK(len() == 2);

        insert_after(len() + 1, ++i);
        TEST_CHECK(head->Data[head->Len - 1] == i);
        TEST_CHECK(len() == 3);

        insert_after(1, ++i);
        TEST_CHECK(head->Data[1] == i);
        TEST_CHECK(len() == 4);

        insert_after(3, ++i);
        TEST_CHECK(head->Data[3] == i);
        TEST_CHECK(len() == 5);

         while (len() != CAPACITY + 1) {
                insert_after(2, ++i);

                if (!TEST_CHECK(i < CAPACITY + 1)) {
                        TEST_MSG("YOU FORGOT INCREASE THE SIZE");
                        break;
                }
        }

        TEST_CHECK(head->Data[0] == 1);
        TEST_CHECK(head->Data[1] == 3);
        TEST_CHECK(head->Next->Data[head->Next->Len - 1] == 2);
        TEST_CHECK(head->Next->Data[0] == 12);
        TEST_CHECK(head->Next->Len == THRESHOLD);

        // display();
}

void test_insert_end()
{
        int i = 0;

        init(69);

        insert_end(++i);
        TEST_CHECK(head->Data[0] == 69);
        TEST_CHECK(head->Data[1] == i);
        TEST_CHECK(len() == 2);

        while (len() != CAPACITY + 1) {
                insert_end(++i);

                if (!TEST_CHECK(i < CAPACITY + 1)) {
                        TEST_MSG("YOU FORGOT INCREASE THE SIZE");
                        break;
                }
        }

        TEST_CHECK(head->Next->Data[0] == i - THRESHOLD + 1);
        TEST_CHECK(head->Next->Data[head->Next->Len - 1] == i);
        TEST_CHECK(head->Next->Data[head->Next->Len - 2] == i - 1);
        TEST_CHECK(head->Next->Len == THRESHOLD);

        // display();
}

void test_multi_insert()
{
        init(69);

        insert_end(7);
        TEST_CHECK(head->Data[0] == 69);
        TEST_CHECK(head->Data[1] == 7);

        insert_beg(8);
        TEST_CHECK(head->Data[0] == 8);
        TEST_CHECK(head->Data[1] == 69);

        insert_after(-1, 9);
        TEST_CHECK(head->Data[0] == 9);
        TEST_CHECK(head->Data[1] == 8);

        insert_end(10);
        TEST_CHECK(head->Data[0] == 9);
        TEST_CHECK(head->Data[head->Len - 1] == 10);

        insert_beg(11);
        TEST_CHECK(head->Data[0] == 11);
        TEST_CHECK(head->Data[1] == 9);

        // display();
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
        TEST_CHECK(head->Data[0] == 69);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data[0] == 1);
        TEST_CHECK(head->Len == MAX - 1);

        delete_first();
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Data[0] == 2);
        TEST_CHECK(head->Len == MAX - 2);
        
        // display();

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

        // display();

        delete_node(0);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());
        TEST_CHECK(head->Data[0] == 1);
        TEST_CHECK(head->Data[1] == 2);

        delete_node(1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());
        TEST_CHECK(head->Data[0] == 2);
        TEST_CHECK(head->Data[1] == 3);

        delete_node(2);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());
        TEST_CHECK(head->Data[1] == 4);
        TEST_CHECK(head->Data[2] == 5);
        
        delete_node(-1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());
        TEST_CHECK(head->Data[0] == 4);
        TEST_CHECK(head->Data[1] == 5);

        delete_node(size);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());

        delete_node(size + 1);
        TEST_CHECK(len() == MAX - count++);
        TEST_CHECK(head->Len == len());
        
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

        // display();

        delete_last();
        TEST_CHECK(len() == 2);
        TEST_CHECK(head->Len == 2);
        TEST_CHECK(head->Data[0] == 69);
        TEST_CHECK(head->Data[1] == 1);
        
        delete_last();
        TEST_CHECK(len() == 1);
        TEST_CHECK(head->Len == 1);
        TEST_CHECK(head->Data[0] == 69);
        
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
        TEST_CHECK(head->Data[0] == 69 && head->Data[2] == 2);
        delete_last();
        TEST_CHECK(head->Data[0] == 69 && head->Data[1] == 1);
        
        insert_beg(3);
        TEST_CHECK(head->Data[0] == 3 && head->Data[1] == 69);
        delete_first();
        TEST_CHECK(head->Data[0] == 69 && head->Data[1] == 1);

        insert_after(1, 5);
        TEST_CHECK(head->Data[0] == 69 && head->Data[1] == 5);
        delete_node(2);
        TEST_CHECK(head->Data[0] == 69 && head->Data[1] == 1);
}

TEST_LIST = {
        { "ARRAY SIZE && THRESHOLD", test_basic },
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
