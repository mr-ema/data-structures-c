#include <stdio.h>
#include <stddef.h>

void xor_swap(int *x, int *y) {
        if (*x == *y)
                return;

        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
}

size_t partition(int *arr, size_t beg, size_t end) {
        size_t middle = (beg + end) / 2;
        int pivot = arr[middle];

        arr[middle] = arr[end];
        arr[end] = pivot;

        size_t pi = beg;
        for (size_t j = beg; j < end; ++j) {
                if (arr[j] < pivot)
                        xor_swap(&arr[pi++], &arr[j]);
        }
        xor_swap(&arr[pi], &arr[end]);

        return pi;
}

void quicksort(int *arr, size_t beg, size_t end) {
        if (beg < end) {
                size_t pi = partition(arr, beg, end);
 
                quicksort(arr, beg, pi);
                quicksort(arr, ++pi, end);
        }
}

int main(void) {
        int arr[] = { 5, 2, 8, 1, 4 };
        int expected[] = { 1, 2, 4, 5, 8 };
        size_t size = sizeof(arr) / sizeof(arr[0]);

        printf("Testing Quicksort:\n");
        quicksort(arr, 0, size - 1);

        printf("Expected: ");
        for (size_t i = 0; i < size; i++) {
                printf("%d ", expected[i]);
        }
        printf("\n");

        printf("Actual:   ");
        for (size_t i = 0; i < size; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");

        return 0;
}
