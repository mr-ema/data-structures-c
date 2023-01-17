# Array - Linear Data Structure
An `array` is a linear data structure that collects elements of the same data type and stores them in contiguous memory locations.

</br>

## Navigation
- **Array**
  - [Static Array](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#static-array)
  - [Definitions](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#definitions)
  - [Sub Array](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#subarray)
  - [Get An Element](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#get-an-element)
  - [Inserting Elements](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#inserting-elements)
  - [Deleting Elements](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#deleting-elements)
  
- **Security**
  - [Segmentation Fault](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#segmentation-fault)
  - [Buffer Overflow](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#buffer-overflow)
  - [Buffer Over-Read](https://github.com/mr-ema/data-structures-c/tree/main/Structures/array#buffer-over-reads)

</br>
</br>

## Resources
- _Low Level Learning_ - Strings in C are getting people HACKED -> [Youtube Video](https://www.youtube.com/watch?v=fjMrDDj47E8)
- _The Geek Stuff_ - Buffer Overflow Attack Explained with a C Program -> [Article](https://www.thegeekstuff.com/2013/06/buffer-overflow)
- _Tutorials Point_ - Operating System - Memory Management -> [Article](https://www.tutorialspoint.com/operating_system/os_memory_management.htm)

</br>
</br>

## Static Array

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-array.svg"
    alt="Static Array Graphical Representation"
    title="Static Array Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

## Definitions
- **Address:** Memory location of the data
- **Array:** A collection of elements of the same data type
- **Size:** Total of elements in the array (6 in the image)
- **Index:** Allows to get an element at a given position
- **Lower Bound:** The first element in an array
- **Upper Bound:** The last element in an array
- **Data Type**: There are multiple types of data but the basics are:

  - **float** takes 4 bytes
  - **int** takes 4 bytes
  - **double** takes 8 bytes
  - **char** takes 1 byte 

</br>
</br>

## SubArray
A subarray is commonly defined as a part or section of an array. **A subarray must maintain the order of the original array**. For example, the subarrays of array `{20, 21, 22}` are `{20}`, `{20, 21}`, `{20, 21, 22}`, `{21}`, `{21, 22}`, and `{22}`. **Now if you alter the original order it would be considered a Subset**. For example, `{22, 21}` is a subset of `{20, 21, 22}`.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/02-array.svg"
    alt="Sub Array Graphical Representation"
    title=" Sub Array Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 90%;">
</p>

#### Method 1
You build a **sub-array** by moving the **lower bound** from 0 to 2 something similar to binary search.
For example, given the **array** with the elements `{20, 21, 22, 23, 24, 25}` if you change `lower bound` to be `2` you will get the **sub-array** `{22, 23, 24, 25}`.
```c
// This is a dummy implementation but a think is a good example of how you can create a sub-array

// initialize array
int arr[6] = {20, 21, 22, 23, 24, 25};

// Define boundaries
int lower_bound = 0;
int upper_bound = 5; // size array - 1

// Create sub-array [22, 23, 24, 25] with boundaries
lower_bound = 2;
upper_bound = 3; // resize array (5 - 2)

// Now you could access the array in the following manner.
int user_input = 2;

// Check if is a vaild position
if (user_input > 0 && user_input < upper_bound)
        printf("%d\n", arr[lower_bound + user_input]);
```

</br>

#### Method 2
You create a pointer to a given address in the array.
For example, in the **array** `{20, 21, 22, 23, 24, 25}` you create a new **pointer variable** let's call it `sub_arr` and you assign it the **address of the element 22 that is 0x18**. Now our pointer will point to **0x18**. Then if you do `sub_arr[0]` you will get **22**.
```c
// initialize array
int arr[6] = {20, 21, 22, 23, 24, 25};

// This will create a pointer to the third element '22'
int *sub_arr = &arr[2];

// Note that since this is a pointer to address '0x18' this will print `22`
printf("%d\n", sub_arr[0]);

// And this will print 21.
// Since: 0x18 + (-1 * 4) = 0x18 - 4 and '0x18 - 4' is equal to '0x14'
printf("%d\n", sub_arr[-1]);

// In C accessing array elements beyond array boundaries (before 0 or from its size up) is undefined behavior.
// To avoid undefined behavior you could do something like this.
int user_input = 2;
int lower_bound = 0;
int upper_bound = 6-2; // 6 = len of arr, 2 = index arr[2]

// Check if is a vaild position
if (user_input > lower_bound && user_input < upper_bound - 1)
        printf("%d\n", sub_arr[user_input]);
```

</br>
</br>

## Get An Element
When you do something like `printf("%d", arr[0])`

#### How does the compiler knows what to print?
It may seem like magic but to understand what is really happening you need to know the following:
- `arr` -> Is a **pointer to the memory address of the first element**
- `[n]` -> Is the index of an array element or **the offset from index 0**
- `data type size` -> Is the size of the data type for example **int takes 4 bytes**

With this information the compiler is able to calculate the memory address of the required element using the following formula:

**_`arr + (offset * data_type_size) = address of element`_**

Also this is why when you do something like arr[-1] you get an invalid adresses or undefined behavior or even buffer overflow.

**_example: arr[0] -> 10 + (0 * 4) = 10 -> returns 20_\
_example: arr[2] -> 10 + (2 * 4) = 18 -> returns 22_**

</br> 

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/03-array.svg"
    alt="Static Array Get An Element Graphical Representation"
    title="Static Array Get An Element Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

**Try It Your Self**
```c
#include <stdio.h>

int main() {
    int arr[3];

    printf("arr:     %p\n", arr);     // pointer to the first element
    printf("&arr[0]: %p\n", &arr[0]); // same as arr
    printf("&arr[1]: %p\n", &arr[1]); // 4 bytes after arr[0]
    printf("&arr[2]: %p\n", &arr[2]); // 8 bytes after arr[0]

    return 0;
}
```

</br>
</br>

## Inserting Elements
We can insert the elements wherever we want, which means we can insert either at starting position or at the middle or at last or anywhere in the array.

</br>

### Inserting At Starting Poisition

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-array.svg"
    alt="Inserting At Starting Poisition Graphic Representation"
    title="Inserting At Starting Poisition Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void insert_beg(int val)
{
        if (is_full()) {
                printf("Array Is Full\n");
                return;
        }

        // Move all elements from the left to the right
        for (int i = len(); i > 0; i--)
                arr[i] = arr[i-1];

        // Over-write first element
        arr[0] = val;
        size++;
}
```

</br>

### Inserting At Given Poisition

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-array.svg"
    alt="Inserting At Given Poisition Graphic Representation"
    title="Inserting At Given Poisition Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void insert_at_pos(int pos, int val)
{
        if (is_full()) {
                printf("Array Is Full\n");
                return;
        } else if (pos < 0 || pos > size) {
                printf("Invalid Position\n");
                return;
        }

        // Move elements from the left to the right
        for (int i = len()+1; i > pos; i--)
                arr[i] = arr[i-1];

        // Over-write element at given position
        arr[pos] = val;
        size++;
}
```

</br>

### Inserting At Ending Poisition

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/06-array.svg"
    alt="Inserting At Ending Poisition Graphic Representation"
    title="Inserting At Ending Poisition Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void insert_end(int val)
{
        if (is_full()) {
                printf("Array Is Full\n");
                return;
        }

        // ++size is the pre-increment operator and is used to increment
        // the value of a variable before using it in an expression.
        arr[++size] = val; // over-write last element.
        
}
```

</br>
</br>

## Deleting Elements
As well as we can insert elements wherever we wany we can also delete them. Which means we can delete either at start or at the middle or at the end or anywhere in the array.

</br>

### Deleting At Begining Of Array

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/07-array.svg"
    alt="Deleting At Begining Of Array Graphic Representation"
    title="Deleting At Begining Of Array Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void delete_beg()
{
        if (is_empty()) {
                printf("Array Is Empty\n");
                return;
        }

        // Same as insert exept that we shift
        // the elements to the left instead of right
        for (int i = 0; i < size; i++)
                arr[i] = arr[i+1];

        size--;
}
```

</br>

### Deleting At Given Poisition

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/08-array.svg"
    alt="Deleting At Given Poisition Graphic Representation"
    title="Deleting At Given Poisition Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void delete_at_pos(int pos)
{
        if (is_empty()) {
                printf("Array Is Empty\n");
                return;
        } else if (pos < 0 || pos > size) {
                printf("Invalid Position\n");
                return;
        }

        // we shift elements after position to the left
        for (int i = pos; i < size; i++)
                arr[i] = arr[i+1];

        size--;
}
```

</br>

### Deleting At End Of Array

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/09-array.svg"
    alt="Deleting At End Of Array Graphic Representation"
    title="Deleting At End Of Array Graphic Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void delete_end()
{
        if (is_empty()) {
                printf("Array Is Empty\n");
                return;
        }

        size--;
}
```

</br>
</br>

## Segmentation Fault
A segmentation fault occurs when a program attempts to access a memory location that it is not allowed to access, or attempts to access a memory location in a way that is not allowed (for example, attempting to write to a read-only location, or to overwrite part of the operating system). **Both buffer overflow and buffer over-read can produce a segmentation fault**. [_here a good explanation_](https://qr.ae/prayGz)

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/10-array.svg"
    alt="Segmentation Fault Graphical Representation"
    title="Segmentation Fault Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
// If you run this and you will get a segmentation fault.

int main()
{
        // A string literal is stored in read only part of data segment
        char *str = "err";
 
        // Let's say *str get allocated in address 0x10 in read only memory
        // This will Try to modify 0x11 read only memory and will produce a Segmentation Fault
        *(str+1) = 'n'; // 0x10 + 1 => 0x11 => 'r'
        
        return 0;
}
```

</br>
</br>

## Buffer Overflow
A buffer overflow occurs when the volume of data exceeds the storage capacity of the memory buffer. As a result, the program attempting to write the data to the buffer overwrites adjacent memory locations.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/11-array.svg"
    alt="Buffer Overflow Graphical Representation"
    title="Buffer Overflow Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
int main()
{
        char buffer[3];
        int i = 3;
 
        // This will over-write the memory located after buffer boundary
        // until a segmentation fault occurs
        while (1) {
                printf("%c", buffer[i]); // before over-write
                buffer[i] = 'x';
                printf("%c", buffer[i++]); // after over-write
        }

        return 0;
}
```

</br>
</br>

## Buffer Over-Reads
A buffer over-read is an anomaly where a program, while reading data from a buffer, overruns the buffer's boundary and reads (or tries to read) adjacent memory.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/12-array.svg"
    alt="Buffer Over-Reads Graphical Representation"
    title="Buffer Over-Reads Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
// This program will print data after the buffer boundary

int main()
{
        char buffer[3];
        
        for (int i = 0; i < 1000; i++) {
                printf("%c", buffer[i]);
        }

        return 0;

}
```
