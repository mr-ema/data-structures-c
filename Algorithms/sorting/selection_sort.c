#include <stdio.h>
#include <stddef.h>

void xor_swap(int *x, int *y) {
        if (*x == *y)
                return;

        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
}

void selection_sort(int *arr, size_t size) {
        size_t min_idx;

        for (size_t i = 0; i < size - 1; i++) {
                min_idx = i;

                for (size_t j = i + 1; j < size; j++) {
                        if (arr[j] < arr[min_idx])
                                min_idx = j;
                }

                if (min_idx != i)
                        xor_swap(&arr[min_idx], &arr[i]);
        }
}

int main(void) {
        int arr[] = { 5, 2, 8, 1, 4 };
        int expected[] = { 1, 2, 4, 5, 8 };
        size_t size = sizeof(arr) / sizeof(arr[0]);

        printf("Testing Selection Sort:\n");
        selection_sort(arr, size);

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
