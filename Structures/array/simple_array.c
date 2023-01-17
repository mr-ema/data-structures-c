#include <stdio.h>

#include "array.h"
#include "acutest.h"

#define N 10

int arr[N];
int size = -1;

int len() {
        return size + 1;
}

int is_full()
{
        return (size >= N - 1);
}

int is_empty()
{
        return (size <= -1);
}

void init()
{
        size = -1;
}

void traverse()
{
        if (is_empty()) {
                printf("Array Is Empty\n");
                return;
        }

        printf("Elements in array are: [ ");

        for (int i = 0; i < len(); i++) {
                printf("%d ", arr[i]);
        }
        printf("]\n");
}

void insert_beg(int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        }

        // Move all elements from the left to the right
        for (int i = len(); i > 0; i--) {
                arr[i] = arr[i-1];
        }

        // Over-write first element
        arr[0] = val;

        size++;
}

void insert_at_pos(int pos, int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        } else if (pos <= 0 || pos >= len()) {
                pos <= 0 ? insert_beg(val) : insert_end(val);
                return;
        }

        // Move elements from the left to the right
        for (int i = len() + 1; i > pos; i--)
                arr[i] = arr[i-1];

        // Over-write element at given position
        arr[pos] = val;

        size++;
}

void insert_end(int val)
{
        if (is_full()) {
                // printf("Overflow Condition\n");
                return;
        }

        // over-write last element
        arr[++size] = val;

}

void delete_beg()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        // Same as insert exept that we shift
        // the elements to the left instead of right
        for (int i = 0; i < len(); i++)
                arr[i] = arr[i+1];

        size--;
}

void delete_at_pos(int pos)
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        } else if (pos <= 0 || pos >= size) {
                pos <= 0 ? delete_beg() : delete_end();
                return;
        }

        // we shift elements after position to the left
        for (int i = pos; i < len(); i++)
                arr[i] = arr[i+1];

        size--;
}

void delete_end()
{
        if (is_empty()) {
                // printf("Underflow Condition\n");
                return;
        }

        size--;
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_min_size()
{
        TEST_CHECK(N >= 10);
        TEST_MSG("N must be greater than 9");
}

void test_insert_beg()
{
        init();

        TEST_CHECK(is_empty());

        insert_beg(1);
        TEST_CHECK(arr[0] == 1);
        TEST_CHECK(!is_empty());
        TEST_CHECK(len() == 1);

        insert_beg(10);
        TEST_CHECK(arr[0] == 10);
        TEST_CHECK(len() == 2);

        for (int i = 0; i < N + 1; i++) {
                insert_beg(1);
        }
        TEST_CASE("OVERFLOW");
        insert_beg(1);
        TEST_CHECK(len() <= N);
}

void test_insert_at_pos()
{
        init();

        TEST_CHECK(is_empty());

        insert_at_pos(0, 20);
        TEST_CHECK(arr[0] == 20);
        TEST_CHECK(!is_empty());
        TEST_CHECK(len() == 1);

        insert_at_pos(-1, 30);
        TEST_CHECK(arr[0] == 30);
        TEST_CHECK(arr[1] == 20);
        
        insert_at_pos(1, 30);
        TEST_CHECK(arr[1] == 30);
        TEST_CHECK(arr[2] == 20);

        insert_at_pos(len() + 1, 30);
        TEST_CHECK(arr[3] == 30);
        TEST_CHECK(arr[2] == 20);

        for (int i = 0; i < N + 1; i++) {
                insert_at_pos(2, 1);
        }
        TEST_CASE("OVERFLOW");
        insert_at_pos(3, 1);
        TEST_CHECK(len() <= N);
}

void test_insert_end()
{
        init();

        TEST_CHECK(is_empty());

        insert_end(2);
        TEST_CHECK(arr[0] == 2);
        TEST_CHECK(!is_empty());
        TEST_CHECK(len() == 1);

        insert_end(3);
        TEST_CHECK(arr[1] == 3);
        TEST_CHECK(len() == 2);

        for (int i = 0; i < N + 1; i++) {
                insert_end(1);
        }
        TEST_CASE("OVERFLOW");
        insert_end(1);
        TEST_CHECK(len() <= N);
}

void test_multi_insert()
{
        init();

        insert_end(2);
        TEST_CHECK(arr[0] == 2);
        TEST_CHECK(len() == 1);

        insert_beg(1);
        TEST_CHECK(arr[0] == 1);
        TEST_CHECK(arr[1] == 2);
        TEST_CHECK(len() == 2);
        
        insert_at_pos(-1, 3);
        TEST_CHECK(arr[0] == 3);
        TEST_CHECK(arr[1] == 1);
        TEST_CHECK(len() == 3);

        insert_at_pos(2, 4);
        TEST_CHECK(arr[0] == 3);
        TEST_CHECK(arr[1] == 1);
        TEST_CHECK(arr[2] == 4);
        TEST_CHECK(arr[3] == 2);
        TEST_CHECK(len() == 4);

        insert_beg(5);
        TEST_CHECK(arr[0] == 5);
        TEST_CHECK(arr[1] == 3);
        TEST_CHECK(arr[2] == 1);
        TEST_CHECK(len() == 5);

        insert_end(5);
        TEST_CHECK(arr[0] == 5);
        TEST_CHECK(arr[1] == 3);
        TEST_CHECK(arr[len()-1] == 5);
        TEST_CHECK(len() == 6);
}

void test_delete_beg()
{
        init();

        TEST_CHECK(is_empty());

        insert_end(1);
        insert_end(2);
        insert_end(3);

        delete_beg();
        TEST_CHECK(len() == 2);
        TEST_CHECK(arr[0] == 2);

        delete_beg();
        TEST_CHECK(len() == 1);
        TEST_CHECK(arr[0] == 3);
        
        delete_beg();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_beg();
        TEST_CHECK(len() == 0);
}

void test_delete_at_pos()
{
        init();

        TEST_CHECK(is_empty());

        insert_end(1);
        insert_end(2);
        insert_end(3);
        insert_end(4);

        delete_at_pos(2);
        TEST_CHECK(arr[2] == 4);
        TEST_CHECK(len() == 3);

        delete_at_pos(len()+1);
        TEST_CHECK(arr[1] == 2);
        TEST_CHECK(len() == 2);

        delete_at_pos(-1);
        TEST_CHECK(arr[0] == 2);
        TEST_CHECK(len() == 1);

         delete_at_pos(9);
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_at_pos(2);
        TEST_CHECK(len() == 0);
}

void test_delete_end()
{
        init();

        TEST_CHECK(is_empty());

        insert_end(1);
        insert_end(2);
        insert_end(3);

        delete_end();
        TEST_CHECK(len() == 2);
        TEST_CHECK(arr[1] == 2);

        delete_end();
        TEST_CHECK(len() == 1);
        TEST_CHECK(arr[0] == 1);

        delete_end();
        TEST_CHECK(len() == 0);

        TEST_CASE("UNDERFLOW");
        delete_end();
        TEST_CHECK(len() == 0);
}

void test_multi_delete()
{
         init();

        TEST_CHECK(is_empty());

        insert_end(1);
        insert_end(2);
        insert_end(3);
        insert_end(4);
        insert_end(5);

        delete_end();
        TEST_CHECK(arr[len()-1] == 4);
        TEST_CHECK(len() == 4);

        delete_at_pos(2);
        TEST_CHECK(arr[2] == 4);
        TEST_CHECK(len() == 3);

        delete_beg();
        TEST_CHECK(arr[0] == 2);
        TEST_CHECK(len() == 2);

        delete_end();
        TEST_CHECK(arr[0] == 2);
        TEST_CHECK(len() == 1);
}

TEST_LIST = {
        { "ARRAY SIZE", test_min_size },

        { "INSERT BEGINNING", test_insert_beg },
        { "INSERT AT POSITION", test_insert_at_pos },
        { "INSERT END", test_insert_end },
        { "INSERT BEGINNING/AT POSITION/END", test_multi_insert },

        { "DELETE BEGINNING", test_delete_beg },
        { "DELETE AT POSITION", test_delete_at_pos },
        { "DELETE END", test_delete_end },
        { "DELETE BEGINNING/AT POSITION/END", test_multi_delete },

        { NULL, NULL }
};
