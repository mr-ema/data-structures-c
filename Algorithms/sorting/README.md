# Sorting Algorithms
A **sorting algorithm** is a set of instructions or steps used to arrange
elements in a specific order. These algorithms take an unsorted collection
of data and reorder it according to a defined criteria.

The process of sorting involves comparing elements and repositioning them
based on their values. Sorting algorithms can vary in their efficiency,
stability, and suitability for different types and sizes of data.

</br>

## Navigation
- [Selection Sort](#selection-sort)
- [Bubble Sort](#bubble-sort)
- [Quicksort](#quicksort)

</br>
</br>

## Resources
- [_GeeksforGeeks_ - Bubble Sort (Video)](https://www.youtube.com/watch?v=nmhjrI-aW5o)

</br>
</br>

## Selection Sort
Selection sort is a simple sorting algorithm that works by repeatedly
finding the minimum element from the unsorted part of the list and
placing it at the beginning. This process is repeated until the entire
list is sorted.

Imagine you have a row of numbers that are not in the correct order,
and you want to sort them using selection sort. Here's how it works:

1. Start at the beginning of the row.
2. Find the minimum element in the unsorted part of the row.
3. Swap the minimum element with the first element of the unsorted part.
4. Move to the next position in the row (the second position now) and repeat steps 2 and 3.
5. Continue this process, finding the minimum element from the remaining unsorted part and swapping it with the next position in the row.
6. Keep going until you reach the end of the row. By this point, the smallest element will have been placed in the first position of the row.
7. Repeat steps 2-6 for the remaining unsorted part of the row, excluding the first element that you already sorted.
8. Keep repeating this process until the entire row is sorted.

</br>
</br>

## Bubble Sort
Bubble sort is a simple sorting algorithm that works by repeatedly going
through a list of elements and comparing adjacent pairs. If the elements
are in the wrong order, they are swapped. This process is repeated until
the entire list is sorted.

Imagine you have a row of numbers that are not in the correct order, and you want to sort them using bubble sort. Here's how it works:

1. Start at the beginning of the row.
2. Compare the first number with the second number. If the first number is greater than the second number, you swap their positions.
3. Move to the next pair of numbers (the second and third numbers) and compare them. Again, swap them if they are in the wrong order.
4. Continue this process, comparing and swapping adjacent numbers as you move along the row.
5. Keep going until you reach the end of the row. By this point, the largest number will have "bubbled up" to the rightmost position.
6. Repeat steps 1-5 for the remaining unsorted part of the row, excluding the last element that you already sorted.
7. Keep repeating this process until the entire row is sorted.

</br>
</br>

## Quicksort
Quicksort is a widely used sorting algorithm that follows the divide-and-conquer approach. It
works by selecting a pivot element from the array and partitioning the other elements into two
sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays
are then recursively sorted.

Here's a step-by-step explanation of the Quicksort algorithm:

1. Choose a pivot element from the array.
2. Partition the array into two sub-arrays:
   - Elements less than the pivot are placed to the left.
   - Elements greater than the pivot are placed to the right.
3. Recursively apply the above steps to the sub-arrays.
   - Choose a pivot for each sub-array.
   - Partition the sub-array into two sub-arrays.
   - Repeat until the sub-arrays have size 0 or 1.
4. The recursion terminates when the entire array is sorted.

