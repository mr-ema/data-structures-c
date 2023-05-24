#include <stdio.h>

#define CAPACITY 10

int arr[CAPACITY];
int size = -1;


int arr_len() {
        return size + 1;
}

int arr_is_full() {
        return (size >= CAPACITY - 1);
}

int arr_is_empty() {
        return (size <= -1);
}

void arr_traverse() {
        if (arr_is_empty()) {
                printf("Array Is Empty\n");
                return;
        }

        printf("Elements in array are: [ ");
        for (int i = 0; i < arr_len(); i++) {
                printf("%d ", arr[i]);
        }
        printf("]\n");
}

void arr_insert_beg(int val) {
        if (arr_is_full()) {
                printf("Overflow Condition\n");
                return;
        }

        // Move all elements from the left to the right
        for (int i = arr_len(); i > 0; i--) {
                arr[i] = arr[i-1];
        }

        // Over-write first element
        arr[0] = val;

        size++;
}

void arr_insert_end(int val) {
        if (arr_is_full()) {
                printf("Overflow Condition\n");
                return;
        }

        // over-write last element
        arr[++size] = val;
}

void arr_insert_at_pos(int pos, int val) {
        if (arr_is_full()) {
                printf("Overflow Condition\n");
                return;
        } else if (pos <= 0 || pos >= arr_len()) {
                pos <= 0 ? arr_insert_beg(val) : arr_insert_end(val);
                return;
        }

        // Move elements from the left to the right
        for (int i = arr_len() + 1; i > pos; i--)
                arr[i] = arr[i-1];

        // Over-write element at given position
        arr[pos] = val;

        size++;
}

void arr_delete_beg() {
        if (arr_is_empty()) {
                printf("Underflow Condition\n");
                return;
        }

        // Same as insert exept that we shift
        // the elements to the left instead of right
        for (int i = 0; i < arr_len(); i++)
                arr[i] = arr[i+1];

        size--;
}

void arr_delete_end() {
        if (arr_is_empty()) {
                printf("Underflow Condition\n");
                return;
        }

        size--;
}

void arr_delete_at_pos(int pos) {
        if (arr_is_empty()) {
                printf("Underflow Condition\n");
                return;
        } else if (pos <= 0 || pos >= size) {
                pos <= 0 ? arr_delete_beg() : arr_delete_end();
                return;
        }

        // we shift elements after position to the left
        for (int i = pos; i < arr_len(); i++)
                arr[i] = arr[i+1];

        size--;
}

int main() {
        // Insert values at the beginning, end, and specific positions
        arr_insert_beg(5);      // Array: [5]
        arr_insert_end(10);     // Array: [5, 10]
        arr_insert_at_pos(1, 7);// Array: [5, 7, 10]
        arr_insert_beg(2);      // Array: [2, 5, 7, 10]
        arr_insert_end(15);     // Array: [2, 5, 7, 10, 15]
        arr_insert_at_pos(3, 12);// Array: [2, 5, 7, 12, 10, 15]
        arr_traverse();         // Elements in array are: [2 5 7 12 10 15]

        // Delete values from the beginning, end, and specific positions
        arr_delete_beg();       // Array: [5, 7, 12, 10, 15]
        arr_delete_end();       // Array: [5, 7, 12, 10]
        arr_delete_at_pos(2);   // Array: [5, 7, 10]
        arr_traverse();         // Elements in array are: [5 7 10]

        return 0;
}
