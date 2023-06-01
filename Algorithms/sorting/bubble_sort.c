#include <stdio.h>

void xor_swap(int *x, int *y) {
        if (*x == *y)
                return;

        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
}

void bubble_sort(int *arr, size_t size) {
        int swapped = 1;

        while (swapped) {
                /* After each iteration, the largest element in the unsorted portion of the array
                 * is guaranteed to be in its correct position at the end of the array.
                 * Therefore, we can safely reduce the size of the unsorted portion by 1. */
                size--;

                swapped = 0;
                for (size_t i = 0; i < size; i++) {
                        if (arr[i] > arr[i + 1]) {
                                xor_swap(&arr[i], &arr[i + 1]);
                                swapped = 1;
                        }
                }
        }
}

void bubble_sort_recursive(int *arr, size_t size) {
        int swapped = 0;

        for (size_t i = 0; i < size - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                        xor_swap(&arr[i], &arr[i + 1]);
                        swapped = 1;
                }
        }

        // If any elements were swapped, recursively call the function with a reduced size
        if (swapped)
                bubble_sort_recursive(arr, size - 1);
}

int main(void) {
        // Test case 1: Bubble Sort
        int arr1[] = {5, 2, 8, 1, 4};
        int expected1[] = {1, 2, 4, 5, 8};
        size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

        bubble_sort(arr1, size1);

        printf("Testing Bubble Sort:\n");
        printf("Expected: ");
        for (size_t i = 0; i < size1; i++) {
                printf("%d ", expected1[i]);
        }
        printf("\n");

        printf("Actual:   ");
        for (size_t i = 0; i < size1; i++) {
                printf("%d ", arr1[i]);
        }
        printf("\n\n");

        // Test case 2: Recursive Bubble Sort
        int arr2[] = {7, 3, 2, 9, 1};
        int expected2[] = {1, 2, 3, 7, 9};
        size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

        bubble_sort_recursive(arr2, size2);

        printf("Testing Recursive Bubble Sort:\n");
        printf("Expected: ");
        for (size_t i = 0; i < size2; i++) {
                printf("%d ", expected2[i]);
        }
        printf("\n");

        printf("Actual:   ");
        for (size_t i = 0; i < size2; i++) {
                printf("%d ", arr2[i]);
        }
        printf("\n\n");

        return 0;
}
