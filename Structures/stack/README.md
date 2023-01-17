# Stack - Linear Data Structure
A `stack`  is a linear type of data structure that follows the **LIFO** (Last-In-First-Out) principle 
and allows insertion and deletion operations from one end of the stack data structure, that is top.

</br>

## Navigation
- **Stack**
  - [Using Array](https://github.com/mr-ema/data-structures-c/tree/main/Structures/stack#using-array)
  - [Using Linked List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/stack#using-linked-list)

- **Operations**
  - [Pop](https://github.com/mr-ema/data-structures-c/tree/main/Structures/stack#pop)
  - [Push](https://github.com/mr-ema/data-structures-c/tree/main/Structures/stack#push)

- **Security**
  - [Stack Overflow](https://github.com/mr-ema/data-structures-c/tree/main/Structures/stack#stack-overflow)

</br>
</br>

## Resources
- _The Call Stack and Stack Overflows_ -> [Youtube Video](https://www.youtube.com/watch?v=jVzSBkbfdiw&list=WL&index=33)
- _Stack Short Animation_ -> [Youtube Video](https://www.youtube.com/watch?v=toRJakeYIKA)
- _Stack Overflow Attack_ -> [Article](https://www.rapid7.com/blog/post/2019/02/19/stack-based-buffer-overflow-attacks-what-you-need-to-know/)

</br>
</br>

## Using Array

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-stack.svg"
    alt="Using Array Graphical Representation"
    title="Using Array Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
#define N 4
 
int stack[N];
int top = -1;

// Fill Stack
top++; // 0
stack[top] = 1;

top++; // 1
stack[top] = 2;

top++; // 2
stack[top] = 3;

top++;  // 3
stack[top] = 4;
```

</br>
</br>

## Using Linked List

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/02-stack.svg"
    alt="Using Linked List Graphical Representation"
    title="Using Linked List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c

struct Node {
        int Data;
        struct Node *Next;
} *top;

int size = 0; 
```

</br>
</br>

## Pop
The `pop` operation will remove the element in `top` of the stack

</br>

### Pop Using Array
When we using an `array` we just decrement `top`.

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/03-stack.svg"
    alt="Pop Operation Array Graphical Representation"
    title="Pop Operation Array Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void pop()
{
        if (top <= 0) {
                // printf("Stack Underflow\n");
                return;
        }
        
        stack[top] = 0; // Optional
        top--;
}
```

</br>

### Pop Using Linked List
When using a `list` we have to free the `node` of `heap` memory.

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-stack.svg"
    alt="Pop Operation Linked List Graphical Representation"
    title="Pop Operation Linked List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void pop()
{
        if (size <= 0) {
                // printf("Stack Underflow\n");
                return;
        }
        
        struct Node *tmp = top;
        
        /* Top is always the head of the list. 
         * When we adding elements we insert them in the begging.
         * Same when we remove them. */
        top = top->Next;
        
        free(tmp);
        size--;
}
```

</br>
</br>

## Push
The `push` operation will add an element top the `top` of the stack

</br>

### Push Using Array
When using an `array` we just increment `top`.

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-stack.svg"
    alt="Push Operation Linked List Graphical Representation"
    title="Push Operation Linked List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void push(int value)
{
        if (top > N) {
                // printf("Stack Overflow\n");
                return;
        }

        stack[top] = N;
        top++;
}
```

</br>

### Push Using Linked List
When using a `list` we have to allocate a `node` in `heap` memory.

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/06-stack.svg"
    alt="Push Operation Linked List Graphical Representation"
    title="Push Operation Linked List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
void push(int value)
{
        /* This will create a new node which will point to the current top node.
         * This is like inserting in the beggining  of a list. */
        top = new_node(value, top);
        size++;
}
```

</br>
</br>

## Stack Overflow
A `stack overflow` **is a type of buffer overflow error that occurs when a computer program tries to use more memory space in the call stack than has been allocated to that stack.**

</br>

_Graphical Representation_
<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/07-stack.svg"
    alt="Stack Overflow Graphical Representation"
    title="Stack Overflow Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 85%;">
</p>

#### This Code Will Produce Stack Overflow
```c
/* This Recursive Function Will Be Allocated In The Call Stack.
 * We Will Call The Function Over And Over Unitil The Call Stack Is Full.
 * Finally The Program Will Crash (Segmentation Fault) */
void infinite_recursion(int n) {
        infinite_recursion(n + 1);
}

int main() {
        // Get Call Until The Program Crash
        infinite_recursion(0);
        
        return 0;
}
```
