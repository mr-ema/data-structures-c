#include <stdio.h>
#include <assert.h>

/**
 * Bubble sort is a simple sorting algorithm that works by repeatedly going
 * through a list of elements and comparing adjacent pairs. If the elements are in the wrong
 * order, they are swapped. This process is repeated until the entire list is sorted.
 *
 *
 * Imagine you have a row of numbers that are not in the correct order, and you want to sort
 * them using bubble sort. Here's how it works:
 *
 *  1. Start at the beginning of the row.
 *  2. Compare the first number with the second number. If the first number is greater than the second number, you swap their positions.
 *  3. Move to the next pair of numbers (the second and third numbers) and compare them. Again, swap them if they are in the wrong order.
 *  4. Continue this process, comparing and swapping adjacent numbers as you move along the row.
 *  5. Keep going until you reach the end of the row. By this point, the largest number will have "bubbled up" to the rightmost position.
 *  6. Repeat steps 1-5 for the remaining unsorted part of the row, excluding the last element that you already sorted.
 *  7. Keep repeating this process until the entire row is sorted.
 */


/**
 * Swaps the values of two integer variables.
 *
 * @param x Pointer to the first integer variable.
 * @param y Pointer to the second integer variable.
 */
void xor_swap(int *x, int *y)
{
        if (*x == *y)
                return;

        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
}

/**
 * Sorts an array of integers in ascending order using the bubble sort algorithm.
 *
 * @param arr   Pointer to the array to be sorted.
 * @param size  The number of elements in the array.
 */
void bubble_sort(int *arr, size_t size)
{
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

/**
 * Sorts an array of integers in ascending order using the recursive Bubble Sort algorithm.
 *
 * @param arr  Pointer to the array of integers.
 * @param size The number of elements in the array.
 */
void bubble_sort_recursive(int *arr, size_t size)
{
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

// Test cases
void test_bubble_sort()
{
        int arr1[] = { 5, 2, 8, 1, 4 };
        int expected1[] = { 1, 2, 4, 5, 8 };
        size_t size1 = sizeof(arr1)/sizeof(arr1[0]);

        bubble_sort(arr1, size1);

        for (size_t i = 0; i < size1; i++)
                assert(arr1[i] == expected1[i]);

        int arr2[] = {7, 3, 2, 9, 1};
        int expected2[] = {1, 2, 3, 7, 9};
        size_t size2 = sizeof(arr2)/sizeof(arr2[0]);

        bubble_sort(arr2, size2);

        for (size_t i = 0; i < size2; i++)
                assert(arr2[i] == expected2[i]);
}

void test_bubble_sort_recursive()
{
        int arr1[] = { 5, 2, 8, 1, 4 };
        int expected1[] = { 1, 2, 4, 5, 8 };
        size_t size1 = sizeof(arr1)/sizeof(arr1[0]);

        bubble_sort_recursive(arr1, size1);

        for (size_t i = 0; i < size1; i++)
                assert(arr1[i] == expected1[i]);

        int arr2[] = {7, 3, 2, 9, 1};
        int expected2[] = {1, 2, 3, 7, 9};
        size_t size2 = sizeof(arr2)/sizeof(arr2[0]);

        bubble_sort_recursive(arr2, size2);

        for (size_t i = 0; i < size2; i++)
                assert(arr2[i] == expected2[i]);
}

int main(void)
{
    test_bubble_sort();
    test_bubble_sort_recursive();
    printf("All tests passed successfully.\n");

    return 0;
}
