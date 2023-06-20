#include <stdio.h>
#include <stddef.h>

void insertion_sort(int *arr, size_t size) {
        int key;
        long j;

        for (size_t i = 1; i < size; i++) {
                key = arr[i];

                for (j = i - 1; j >= 0 && arr[j] > key; j--) {
                        arr[j + 1] = arr[j];
                }
                arr[j + 1] = key;
        }
}

int main(void) {
        int arr[] = { 5, 2, 8, 1, 4 };
        int expected[] = { 1, 2, 4, 5, 8 };
        size_t size = sizeof(arr) / sizeof(arr[0]);

        printf("Testing Insertion Sort:\n");
        insertion_sort(arr, size);

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
